#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_scd_train_param_t ;
typedef  int /*<<< orphan*/  ccv_scd_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

ccv_scd_classifier_cascade_t* ccv_scd_classifier_cascade_new(ccv_array_t* posfiles, ccv_array_t* hard_mine, int negative_count, const char* filename, ccv_scd_train_param_t params)
{
#ifdef HAVE_GSL
	assert(posfiles->rnum > 0);
	assert(hard_mine->rnum > 0);
	gsl_rng_env_setup();
	gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
	ccv_scd_classifier_cascade_new_function_state_t z = {0};
	z.features = _ccv_scd_stump_features(params.feature.base, params.feature.range_through, params.feature.step_through, params.size);
	PRINT(CCV_CLI_INFO, " - using %d features\n", z.features->rnum);
	int i, j, p, q;
	z.positives = _ccv_scd_collect_positives(params.size, posfiles, params.grayscale);
	double* h = (double*)ccmalloc(sizeof(double) * (z.positives->rnum + negative_count));
	z.s = (double*)ccmalloc(sizeof(double) * (z.positives->rnum + negative_count));
	assert(z.s);
	z.pw = (double*)ccmalloc(sizeof(double) * z.positives->rnum);
	assert(z.pw);
	z.nw = (double*)ccmalloc(sizeof(double) * negative_count);
	assert(z.nw);
	ccmemalign((void**)&z.fv, 16, sizeof(float) * (z.positives->rnum + negative_count) * z.features->rnum * 32);
	assert(z.fv);
	z.params = params;
	ccv_function_state_begin(_ccv_scd_classifier_cascade_new_function_state_read, z, filename);
	z.negatives = _ccv_scd_collect_negatives(rng, params.size, hard_mine, negative_count, params.grayscale);
	_ccv_scd_precompute_feature_vectors(z.features, z.positives, z.negatives, z.fv);
	z.cascade = (ccv_scd_classifier_cascade_t*)ccmalloc(sizeof(ccv_scd_classifier_cascade_t));
	z.cascade->margin = ccv_margin(0, 0, 0, 0);
	z.cascade->size = params.size;
	z.cascade->count = 0;
	z.cascade->classifiers = 0;
	z.accu_true_positive_rate = 1;
	z.accu_false_positive_rate = 1;
	ccv_function_state_resume(_ccv_scd_classifier_cascade_new_function_state_write, z, filename);
	for (z.t = 0; z.t < params.boosting; z.t++)
	{
		for (i = 0; i < z.positives->rnum; i++)
			z.pw[i] = 0.5 / z.positives->rnum;
		for (i = 0; i < z.negatives->rnum; i++)
			z.nw[i] = 0.5 / z.negatives->rnum;
		memset(z.s, 0, sizeof(double) * (z.positives->rnum + z.negatives->rnum));
		z.cascade->classifiers = (ccv_scd_stump_classifier_t*)ccrealloc(z.cascade->classifiers, sizeof(ccv_scd_stump_classifier_t) * (z.t + 1));
		z.cascade->count = z.t + 1;
		z.cascade->classifiers[z.t].threshold = 0;
		z.cascade->classifiers[z.t].features = 0;
		z.cascade->classifiers[z.t].count = 0;
		z.auc_prev = 0;
		assert(z.positives->rnum > 0 && z.negatives->rnum > 0);
		// for the first prune stages, we have more restrictive number of features (faster)
		for (z.k = 0; z.k < (z.t < params.stop_criteria.prune_stage ? params.stop_criteria.prune_feature : params.stop_criteria.maximum_feature); z.k++)
		{
			ccv_scd_stump_classifier_t* classifier = z.cascade->classifiers + z.t;
			classifier->features = (ccv_scd_stump_feature_t*)ccrealloc(classifier->features, sizeof(ccv_scd_stump_feature_t) * (z.k + 1));
			_ccv_scd_stump_feature_supervised_train(rng, z.features, z.positives->rnum, z.negatives->rnum, z.pw, z.nw, z.fv, params.C, params.weight_trimming);
			int best_feature_no = _ccv_scd_best_feature_gentle_adaboost(z.s, z.features, z.pw, z.nw, z.positives->rnum, z.negatives->rnum, z.fv);
			ccv_scd_stump_feature_t best_feature = *(ccv_scd_stump_feature_t*)ccv_array_get(z.features, best_feature_no);
			for (i = 0; i < z.positives->rnum + z.negatives->rnum; i++)
			{
				float* surf = _ccv_scd_get_surf_at(z.fv, best_feature_no, i, z.positives->rnum, z.negatives->rnum);
				float v = best_feature.bias;
				for (j = 0; j < 32; j++)
					v += best_feature.w[j] * surf[j];
				v = expf(v);
				h[i] = (v - 1) / (v + 1);
			}
			// compute the total score so far
			for (i = 0; i < z.positives->rnum + z.negatives->rnum; i++)
				z.s[i] += h[i];
			// compute AUC
			double auc = _ccv_scd_auc(z.s, z.positives->rnum, z.negatives->rnum);
			float true_positive_rate = 0;
			float false_positive_rate = 0;
			// compute true positive / false positive rate
			_ccv_scd_threshold_at_hit_rate(z.s, z.positives->rnum, z.negatives->rnum, params.stop_criteria.hit_rate, &true_positive_rate, &false_positive_rate);
			FLUSH(CCV_CLI_INFO, " - at %d-th iteration, auc: %lf, TP rate: %f, FP rate: %f\n", z.k + 1, auc, true_positive_rate, false_positive_rate);
			PRINT(CCV_CLI_INFO, " --- pick feature %s @ (%d, %d, %d, %d)\n", ((best_feature.dy[3] == best_feature.dy[0] ? "4x1" : (best_feature.dx[3] == best_feature.dx[0] ? "1x4" : "2x2"))), best_feature.sx[0], best_feature.sy[0], best_feature.dx[3], best_feature.dy[3]);
			classifier->features[z.k] = best_feature;
			classifier->count = z.k + 1;
			double auc_prev = z.auc_prev;
			z.auc_prev = auc;
			// auc stop to improve, as well as the false positive rate goal reach, at that point, we stop
			if (auc - auc_prev < params.stop_criteria.auc_crit && false_positive_rate < params.stop_criteria.false_positive_rate)
				break;
			// re-weight, with Gentle AdaBoost
			for (i = 0; i < z.positives->rnum; i++)
				z.pw[i] *= exp(-h[i]);
			for (i = 0; i < z.negatives->rnum; i++)
				z.nw[i] *= exp(h[i + z.positives->rnum]);
			// re-normalize
			double w = 0;
			for (i = 0; i < z.positives->rnum; i++)
				w += z.pw[i];
			w = 0.5 / w;
			for (i = 0; i < z.positives->rnum; i++)
				z.pw[i] *= w;
			w = 0;
			for (i = 0; i < z.negatives->rnum; i++)
				w += z.nw[i];
			w = 0.5 / w;
			for (i = 0; i < z.negatives->rnum; i++)
				z.nw[i] *= w;
			ccv_function_state_resume(_ccv_scd_classifier_cascade_new_function_state_write, z, filename);
		}
		// backtrack removal
		while (z.cascade->classifiers[z.t].count > 1)
		{
			double max_auc = 0;
			p = -1;
			for (i = 0; i < z.cascade->classifiers[z.t].count; i++)
			{
				ccv_scd_stump_feature_t* feature = z.cascade->classifiers[z.t].features + i;
				int k = _ccv_scd_find_match_feature(feature, z.features);
				assert(k >= 0);
				for (j = 0; j < z.positives->rnum + z.negatives->rnum; j++)
				{
					float* surf = _ccv_scd_get_surf_at(z.fv, k, j, z.positives->rnum, z.negatives->rnum);
					float v = feature->bias;
					for (q = 0; q < 32; q++)
						v += feature->w[q]* surf[q];
					v = expf(v);
					h[j] = z.s[j] - (v - 1) / (v + 1);
				}
				double auc = _ccv_scd_auc(h, z.positives->rnum, z.negatives->rnum);
				FLUSH(CCV_CLI_INFO, " - attempting without %d-th feature, auc: %lf", i + 1, auc);
				if (auc >= max_auc)
					max_auc = auc, p = i;
			}
			if (max_auc >= z.auc_prev)
			{
				FLUSH(CCV_CLI_INFO, " - remove %d-th feature with new auc %lf\n", p + 1, max_auc);
				ccv_scd_stump_feature_t* feature = z.cascade->classifiers[z.t].features + p;
				int k = _ccv_scd_find_match_feature(feature, z.features);
				assert(k >= 0);
				for (j = 0; j < z.positives->rnum + z.negatives->rnum; j++)
				{
					float* surf = _ccv_scd_get_surf_at(z.fv, k, j, z.positives->rnum, z.negatives->rnum);
					float v = feature->bias;
					for (q = 0; q < 32; q++)
						v += feature->w[q] * surf[q];
					v = expf(v);
					z.s[j] -= (v - 1) / (v + 1);
				}
				z.auc_prev = _ccv_scd_auc(z.s, z.positives->rnum, z.negatives->rnum);
				--z.cascade->classifiers[z.t].count;
				if (p < z.cascade->classifiers[z.t].count)
					memmove(z.cascade->classifiers[z.t].features + p + 1, z.cascade->classifiers[z.t].features + p, sizeof(ccv_scd_stump_feature_t) * (z.cascade->classifiers[z.t].count - p));
			} else
				break;
		}
		float true_positive_rate = 0;
		float false_positive_rate = 0;
		z.cascade->classifiers[z.t].threshold = _ccv_scd_threshold_at_hit_rate(z.s, z.positives->rnum, z.negatives->rnum, params.stop_criteria.hit_rate, &true_positive_rate, &false_positive_rate);
		z.accu_true_positive_rate *= true_positive_rate;
		z.accu_false_positive_rate *= false_positive_rate;
		FLUSH(CCV_CLI_INFO, " - %d-th stage classifier TP rate : %f, FP rate : %f, ATP rate : %lf, AFP rate : %lg, at threshold : %f\n", z.t + 1, true_positive_rate, false_positive_rate, z.accu_true_positive_rate, z.accu_false_positive_rate, z.cascade->classifiers[z.t].threshold);
		if (z.accu_false_positive_rate < params.stop_criteria.accu_false_positive_rate)
			break;
		ccv_function_state_resume(_ccv_scd_classifier_cascade_new_function_state_write, z, filename);
		if (z.t < params.boosting - 1)
		{
			int pass = 0;
			for (i = 0; i < z.positives->rnum; i++)
			{
				ccv_dense_matrix_t* a = (ccv_dense_matrix_t*)ccv_array_get(z.positives, i);
				a->data.u8 = (unsigned char*)(a + 1);
				if (_ccv_scd_classifier_cascade_pass(z.cascade, a))
					++pass;
			}
			PRINT(CCV_CLI_INFO, " - %d-th stage classifier TP rate (with pass) : %f\n", z.t + 1, (float)pass / z.positives->rnum);
			ccv_array_t* hard_negatives = _ccv_scd_hard_mining(rng, z.cascade, hard_mine, z.negatives, negative_count, params.grayscale, z.t < params.stop_criteria.prune_stage /* try to balance even distribution among negatives when we are in prune stage */);
			ccv_array_free(z.negatives);
			z.negatives = hard_negatives;
			_ccv_scd_precompute_feature_vectors(z.features, z.positives, z.negatives, z.fv);
		}
		ccv_function_state_resume(_ccv_scd_classifier_cascade_new_function_state_write, z, filename);
	}
	ccv_array_free(z.negatives);
	ccv_function_state_finish();
	ccv_array_free(z.features);
	ccv_array_free(z.positives);
	ccfree(h);
	ccfree(z.s);
	ccfree(z.pw);
	ccfree(z.nw);
	ccfree(z.fv);
	gsl_rng_free(rng);
	return z.cascade;
#else
	assert(0 && "ccv_scd_classifier_cascade_new requires GSL library and support");
	return 0;
#endif
}