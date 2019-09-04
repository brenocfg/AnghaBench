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
typedef  int /*<<< orphan*/  ccv_icf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void ccv_icf_classifier_cascade_soft(ccv_icf_classifier_cascade_t* cascade, ccv_array_t* posfiles, double acceptance)
{
#ifdef HAVE_GSL
	PRINT(CCV_CLI_INFO, "with %d positive examples\n"
						"going to accept %.2lf%% positive examples\n",
		   posfiles->rnum, acceptance * 100);
	ccv_size_t size = ccv_size(cascade->size.width - cascade->margin.left - cascade->margin.right, cascade->size.height - cascade->margin.top - cascade->margin.bottom);
	PRINT(CCV_CLI_INFO, "use color? %s\n", cascade->grayscale ? "no" : "yes");
	PRINT(CCV_CLI_INFO, "compute soft cascading thresholds for ICF classifier cascade at size %dx%d with margin (%d,%d,%d,%d)\n"
						"------------------------\n",
		   size.width, size.height, cascade->margin.left, cascade->margin.top, cascade->margin.right, cascade->margin.bottom);
	gsl_rng_env_setup();
	gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
	/* collect positives */
	double weigh[2] = {
		0, 0
	};
	int i;
	for (i = 0; i < cascade->count; i++)
	{
		ccv_icf_decision_tree_t* weak_classifier = cascade->weak_classifiers + i;
		weigh[0] += weak_classifier->weigh[0];
		weigh[1] += weak_classifier->weigh[1];
	}
	weigh[0] = 1 / fabs(weigh[0]), weigh[1] = 1 / fabs(weigh[1]);
	for (i = 0; i < cascade->count; i++)
	{
		ccv_icf_decision_tree_t* weak_classifier = cascade->weak_classifiers + i;
		weak_classifier->weigh[0] = weak_classifier->weigh[0] * weigh[0];
		weak_classifier->weigh[1] = weak_classifier->weigh[1] * weigh[1];
	}
	ccv_array_t* validates = _ccv_icf_collect_validates(rng, size, cascade->margin, posfiles, cascade->grayscale);
	/* compute soft cascading thresholds */
	_ccv_icf_classifier_cascade_soft_with_validates(validates, cascade, acceptance);
	ccv_array_free(validates);
	gsl_rng_free(rng);
#else
	assert(0 && "ccv_icf_classifier_cascade_soft requires GSL library support");
#endif
}