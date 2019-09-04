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
typedef  int /*<<< orphan*/  ccv_icf_new_param_t ;
typedef  int /*<<< orphan*/  ccv_icf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

ccv_icf_classifier_cascade_t* ccv_icf_classifier_cascade_new(ccv_array_t* posfiles, int posnum, ccv_array_t* bgfiles, int negnum, ccv_array_t* validatefiles, const char* dir, ccv_icf_new_param_t params)
{
#ifdef HAVE_GSL
	_ccv_icf_check_params(params);
	assert(posfiles->rnum > 0);
	assert(bgfiles->rnum > 0);
	assert(posnum > 0 && negnum > 0);
	PRINT(CCV_CLI_INFO, "with %d positive examples and %d negative examples\n"
						"positive examples are going to be collected from %d positive images\n"
						"negative examples are are going to be collected from %d background images\n",
						posnum, negnum, posfiles->rnum, bgfiles->rnum);
	PRINT(CCV_CLI_INFO, "use color? %s\n", params.grayscale ? "no" : "yes");
	PRINT(CCV_CLI_INFO, "feature pool size : %d\n"
						"weak classifier count : %d\n"
						"soft cascade acceptance : %lf\n"
						"minimum dimension of ICF feature : %d\n"
						"number of bootstrap : %d\n"
						"distortion on translation : %f\n"
						"distortion on rotation : %f\n"
						"distortion on scale : %f\n"
						"learn ICF classifier cascade at size %dx%d with margin (%d,%d,%d,%d)\n"
						"------------------------\n",
						params.feature_size, params.weak_classifier, params.acceptance, params.min_dimension, params.bootstrap, params.deform_shift, params.deform_angle, params.deform_scale, params.size.width, params.size.height, params.margin.left, params.margin.top, params.margin.right, params.margin.bottom);
	gsl_rng_env_setup();
	gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
	// we will keep all states inside this structure for easier save / resume across process
	// this should work better than ad-hoc one we used in DPM / BBF implementation
	ccv_icf_classifier_cascade_state_t z;
	z.params = params;
	ccv_function_state_begin(_ccv_icf_read_classifier_cascade_state, z, dir);
	z.classifier->grayscale = params.grayscale;
	z.size = params.size;
	z.margin = params.margin;
	z.classifier->size = ccv_size(z.size.width + z.margin.left + z.margin.right, z.size.height + z.margin.top + z.margin.bottom);
	z.features = (ccv_icf_feature_t*)ccmalloc(sizeof(ccv_icf_feature_t) * params.feature_size);
	// generate random features
	for (z.i = 0; z.i < params.feature_size; z.i++)
		_ccv_icf_randomize_feature(rng, z.classifier->size, params.min_dimension, z.features + z.i, params.grayscale);
	z.x.features = 0;
	ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
	z.positives = _ccv_icf_collect_positives(rng, z.size, z.margin, posfiles, posnum, params.deform_angle, params.deform_scale, params.deform_shift, params.grayscale);
	z.x.positives = 0;
	ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
	z.negatives = _ccv_icf_collect_negatives(rng, z.size, z.margin, bgfiles, negnum, params.deform_angle, params.deform_scale, params.deform_shift, params.grayscale);
	z.x.negatives = 0;
	ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
	for (z.bootstrap = 0; z.bootstrap <= params.bootstrap; z.bootstrap++)
	{
		z.example_state = (ccv_icf_example_state_t*)ccmalloc(sizeof(ccv_icf_example_state_t) * (z.negatives->rnum + z.positives->rnum));
		memset(z.example_state, 0, sizeof(ccv_icf_example_state_t) * (z.negatives->rnum + z.positives->rnum));
		for (z.i = 0; z.i < z.positives->rnum + z.negatives->rnum; z.i++)
			z.example_state[z.i].weight = (z.i < z.positives->rnum) ? 0.5 / z.positives->rnum : 0.5 / z.negatives->rnum;
		z.x.example_state = 0;
		ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
		z.precomputed = _ccv_icf_precompute_features(z.features, params.feature_size, z.positives, z.negatives);
		z.x.precomputed = 0;
		ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
		for (z.i = 0; z.i < params.weak_classifier; z.i++)
		{
			z.classifier->count = z.i + 1;
			PRINT(CCV_CLI_INFO, " - boost weak classifier %d of %d\n", z.i + 1, params.weak_classifier);
			int j;
			ccv_icf_decision_tree_t weak_classifier;
			double rate = _ccv_icf_find_best_weak_classifier(z.features, params.feature_size, z.positives, z.negatives, z.precomputed, z.example_state, &weak_classifier);
			assert(rate > 0.5); // it has to be better than random chance
#ifdef USE_SANITY_ASSERTION
			double confirm_rate = _ccv_icf_rate_weak_classifier(&weak_classifier, z.positives, z.negatives, z.example_state);
#endif
			double alpha = sqrt((1 - rate) / rate);
			double beta = 1.0 / alpha;
			double c = log(rate / (1 - rate));
			weak_classifier.weigh[0] = -c;
			weak_classifier.weigh[1] = c;
			weak_classifier.threshold = 0;
			double reweigh = 0;
			for (j = 0; j < z.positives->rnum + z.negatives->rnum; j++)
			{
				z.example_state[j].weight *= (z.example_state[j].correct) ? alpha : beta;
				z.example_state[j].rate += weak_classifier.weigh[!((j < z.positives->rnum) ^ z.example_state[j].correct)];
				reweigh += z.example_state[j].weight;
			}
			reweigh = 1.0 / reweigh;
#ifdef USE_SANITY_ASSERTION
			PRINT(CCV_CLI_INFO, " - on all examples, best feature at rate %lf, confirm rate %lf\n", rate, confirm_rate);
#else
			PRINT(CCV_CLI_INFO, " - on all examples, best feature at rate %lf\n", rate);
#endif
			// balancing the weight to sum 1.0
			for (j = 0; j < z.positives->rnum + z.negatives->rnum; j++)
				z.example_state[j].weight *= reweigh;
			z.classifier->weak_classifiers[z.i] = weak_classifier;
			// compute the threshold at given acceptance
			float threshold = z.example_state[0].rate;
			for (j = 1; j < z.positives->rnum; j++)
				if (z.example_state[j].rate < threshold)
					threshold = z.example_state[j].rate;
			int true_positives = 0, false_positives = 0;
			for (j = 0; j < z.positives->rnum; j++)
				if (z.example_state[j].rate >= threshold)
					++true_positives;
			for (j = z.positives->rnum; j < z.positives->rnum + z.negatives->rnum; j++)
				if (z.example_state[j].rate >= threshold)
					++false_positives;
			PRINT(CCV_CLI_INFO, " - at threshold %f, true positive rate: %f%%, false positive rate: %f%% (%d)\n", threshold, (float)true_positives * 100 / z.positives->rnum, (float)false_positives * 100 / z.negatives->rnum, false_positives);
			PRINT(CCV_CLI_INFO, " - first feature :\n");
			for (j = 0; j < weak_classifier.features[0].count; j++)
				PRINT(CCV_CLI_INFO, " - %d - (%d, %d) - (%d, %d)\n", weak_classifier.features[0].channel[j], weak_classifier.features[0].sat[j * 2].x, weak_classifier.features[0].sat[j * 2].y, weak_classifier.features[0].sat[j * 2 + 1].x, weak_classifier.features[0].sat[j * 2 + 1].y);
			if (weak_classifier.pass & 0x2)
			{
				PRINT(CCV_CLI_INFO, " - second feature, on left :\n");
				for (j = 0; j < weak_classifier.features[1].count; j++)
					PRINT(CCV_CLI_INFO, " - | - %d - (%d, %d) - (%d, %d)\n", weak_classifier.features[1].channel[j], weak_classifier.features[1].sat[j * 2].x, weak_classifier.features[1].sat[j * 2].y, weak_classifier.features[1].sat[j * 2 + 1].x, weak_classifier.features[1].sat[j * 2 + 1].y);
			}
			if (weak_classifier.pass & 0x1)
			{
				PRINT(CCV_CLI_INFO, " - second feature, on right :\n");
				for (j = 0; j < weak_classifier.features[2].count; j++)
					PRINT(CCV_CLI_INFO, " - | - %d - (%d, %d) - (%d, %d)\n", weak_classifier.features[2].channel[j], weak_classifier.features[2].sat[j * 2].x, weak_classifier.features[2].sat[j * 2].y, weak_classifier.features[2].sat[j * 2 + 1].x, weak_classifier.features[2].sat[j * 2 + 1].y);
			}
			z.classifier->count = z.i + 1; // update count
			z.classifier->size = ccv_size(z.size.width + z.margin.left + z.margin.right, z.size.height + z.margin.top + z.margin.bottom);
			z.classifier->margin = z.margin;
			if (z.i + 1 < params.weak_classifier)
			{
				z.x.example_state = 0;
				z.x.classifier = 0;
				ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
			}
		}
		if (z.bootstrap < params.bootstrap) // collecting negatives, again
		{
			// free expensive memory
			ccfree(z.example_state);
			z.example_state = 0;
			ccfree(z.precomputed);
			z.precomputed = 0;
			_ccv_icf_classifier_cascade_soft_with_validates(z.positives, z.classifier, 1); // assuming perfect score, what's the soft cascading will be
			int exists = z.negatives->rnum;
			int spread_policy = z.bootstrap < 2; // we don't spread bootstrapping anymore after the first two bootstrappings
			// try to boostrap half negatives from perfect scoring
			_ccv_icf_bootstrap_negatives(z.classifier, z.negatives, rng, bgfiles, (negnum + 1) / 2, params.grayscale, spread_policy, params.detector);
			int leftover = negnum - (z.negatives->rnum - exists);
			if (leftover > 0)
			{
				// if we cannot get enough negative examples, now will use the validates data set to extract more
				ccv_array_t* validates = _ccv_icf_collect_validates(rng, z.size, z.margin, validatefiles, params.grayscale);
				_ccv_icf_classifier_cascade_soft_with_validates(validates, z.classifier, params.acceptance);
				ccv_array_free(validates);
				_ccv_icf_bootstrap_negatives(z.classifier, z.negatives, rng, bgfiles, leftover, params.grayscale, spread_policy, params.detector);
			}
			PRINT(CCV_CLI_INFO, " - after %d bootstrapping, learn with %d positives and %d negatives\n", z.bootstrap + 1, z.positives->rnum, z.negatives->rnum);
			z.classifier->count = 0; // reset everything
			z.x.negatives = 0;
		} else {
			z.x.example_state = 0;
			z.x.classifier = 0;
			ccv_function_state_resume(_ccv_icf_write_classifier_cascade_state, z, dir);
		}
	}
	if (z.precomputed)
		ccfree(z.precomputed);
	if (z.example_state)
		ccfree(z.example_state);
	ccfree(z.features);
	ccv_array_free(z.positives);
	ccv_array_free(z.negatives);
	gsl_rng_free(rng);
	ccv_function_state_finish();
	return z.classifier;
#else
	assert(0 && "ccv_icf_classifier_cascade_new requires GSL library support");
	return 0;
#endif
}