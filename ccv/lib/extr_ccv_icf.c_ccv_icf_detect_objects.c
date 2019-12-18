#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ min_neighbors; } ;
typedef  TYPE_3__ ccv_icf_param_t ;
typedef  int /*<<< orphan*/  ccv_icf_multiscale_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_icf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_22__ {scalar_t__ id; scalar_t__ confidence; } ;
struct TYPE_21__ {scalar_t__ width; scalar_t__ height; int x; int y; } ;
struct TYPE_24__ {scalar_t__ neighbors; TYPE_2__ classification; TYPE_1__ rect; } ;
typedef  TYPE_4__ ccv_comp_t ;
struct TYPE_25__ {int rnum; } ;
typedef  TYPE_5__ ccv_array_t ;

/* Variables and functions */
#define  CCV_ICF_CLASSIFIER_TYPE_A 129 
#define  CCV_ICF_CLASSIFIER_TYPE_B 128 
 int /*<<< orphan*/  _ccv_icf_detect_objects_with_classifier_cascade (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,TYPE_3__,TYPE_5__**) ; 
 int /*<<< orphan*/  _ccv_icf_detect_objects_with_multiscale_classifier_cascade (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,TYPE_3__,TYPE_5__**) ; 
 int /*<<< orphan*/  _ccv_is_equal_same_class ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  ccfree (TYPE_4__*) ; 
 int /*<<< orphan*/  ccv_array_clear (TYPE_5__*) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_5__*) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int ccv_array_group (TYPE_5__*,TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_5__*,TYPE_4__*) ; 
 double ccv_min (scalar_t__,scalar_t__) ; 

ccv_array_t* ccv_icf_detect_objects(ccv_dense_matrix_t* a, void* cascade, int count, ccv_icf_param_t params)
{
	assert(count > 0);
	int i, j, k;
	int type = *(((int**)cascade)[0]);
	for (i = 1; i < count; i++)
	{
		// check all types to be the same
		assert(*(((int**)cascade)[i]) == type);
	}
	ccv_array_t** seq = (ccv_array_t**)alloca(sizeof(ccv_array_t*) * count);
	for (i = 0; i < count; i++)
		seq[i] = ccv_array_new(sizeof(ccv_comp_t), 64, 0);
	switch (type)
	{
		case CCV_ICF_CLASSIFIER_TYPE_A:
			_ccv_icf_detect_objects_with_classifier_cascade(a, (ccv_icf_classifier_cascade_t**)cascade, count, params, seq);
			break;
		case CCV_ICF_CLASSIFIER_TYPE_B:
			_ccv_icf_detect_objects_with_multiscale_classifier_cascade(a, (ccv_icf_multiscale_classifier_cascade_t**)cascade, count, params, seq);
			break;
	}
	ccv_array_t* result_seq = ccv_array_new(sizeof(ccv_comp_t), 64, 0);
	ccv_array_t* seq2 = ccv_array_new(sizeof(ccv_comp_t), 64, 0);
	for (k = 0; k < count; k++)
	{
		/* the following code from OpenCV's haar feature implementation */
		if(params.min_neighbors == 0)
		{
			for (i = 0; i < seq[k]->rnum; i++)
			{
				ccv_comp_t* comp = (ccv_comp_t*)ccv_array_get(seq[k], i);
				ccv_array_push(result_seq, comp);
			}
		} else {
			ccv_array_t* idx_seq = 0;
			ccv_array_clear(seq2);
			// group retrieved rectangles in order to filter out noise
			int ncomp = ccv_array_group(seq[k], &idx_seq, _ccv_is_equal_same_class, 0);
			ccv_comp_t* comps = (ccv_comp_t*)cccalloc(ncomp + 1, sizeof(ccv_comp_t));

			// count number of neighbors
			for (i = 0; i < seq[k]->rnum; i++)
			{
				ccv_comp_t r1 = *(ccv_comp_t*)ccv_array_get(seq[k], i);
				int idx = *(int*)ccv_array_get(idx_seq, i);

				comps[idx].classification.id = r1.classification.id;
				if (r1.classification.confidence > comps[idx].classification.confidence || comps[idx].neighbors == 0)
				{
					comps[idx].rect = r1.rect;
					comps[idx].classification.confidence = r1.classification.confidence;
				}

				++comps[idx].neighbors;
			}

			// calculate average bounding box
			for (i = 0; i < ncomp; i++)
			{
				int n = comps[i].neighbors;
				if (n >= params.min_neighbors)
					ccv_array_push(seq2, comps + i);
			}

			// filter out large object rectangles contains small object rectangles
			for (i = 0; i < seq2->rnum; i++)
			{
				ccv_comp_t* r2 = (ccv_comp_t*)ccv_array_get(seq2, i);
				int distance = (int)(ccv_min(r2->rect.width, r2->rect.height) * 0.25 + 0.5);
				for (j = 0; j < seq2->rnum; j++)
				{
					ccv_comp_t r1 = *(ccv_comp_t*)ccv_array_get(seq2, j);
					if (i != j &&
						abs(r1.classification.id) == r2->classification.id &&
						r1.rect.x >= r2->rect.x - distance &&
						r1.rect.y >= r2->rect.y - distance &&
						r1.rect.x + r1.rect.width <= r2->rect.x + r2->rect.width + distance &&
						r1.rect.y + r1.rect.height <= r2->rect.y + r2->rect.height + distance &&
						// if r1 (the smaller one) is better, mute r2
						(r2->classification.confidence <= r1.classification.confidence && r2->neighbors < r1.neighbors))
					{
						r2->classification.id = -r2->classification.id;
						break;
					}
				}
			}

			// filter out small object rectangles inside large object rectangles
			for (i = 0; i < seq2->rnum; i++)
			{
				ccv_comp_t r1 = *(ccv_comp_t*)ccv_array_get(seq2, i);
				if (r1.classification.id > 0)
				{
					int flag = 1;

					for (j = 0; j < seq2->rnum; j++)
					{
						ccv_comp_t r2 = *(ccv_comp_t*)ccv_array_get(seq2, j);
						int distance = (int)(ccv_min(r2.rect.width, r2.rect.height) * 0.25 + 0.5);

						if (i != j &&
							abs(r1.classification.id) == abs(r2.classification.id) &&
							r1.rect.x >= r2.rect.x - distance &&
							r1.rect.y >= r2.rect.y - distance &&
							r1.rect.x + r1.rect.width <= r2.rect.x + r2.rect.width + distance &&
							r1.rect.y + r1.rect.height <= r2.rect.y + r2.rect.height + distance &&
							// if r2 is better, we mute r1
							(r2.classification.confidence > r1.classification.confidence || r2.neighbors >= r1.neighbors))
						{
							flag = 0;
							break;
						}
					}

					if (flag)
						ccv_array_push(result_seq, &r1);
				}
			}
			ccv_array_free(idx_seq);
			ccfree(comps);
		}
		ccv_array_free(seq[k]);
	}
	ccv_array_free(seq2);

	return result_seq;
}