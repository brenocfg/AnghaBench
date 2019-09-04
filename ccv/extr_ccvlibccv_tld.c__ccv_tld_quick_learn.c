#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_30__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_26__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sfmt_t ;
typedef  int /*<<< orphan*/  dsfmt_t ;
struct TYPE_44__ {float nnc_collect; int track_deform; int rotation; scalar_t__ exclude_overlap; int /*<<< orphan*/  track_deform_shift; int /*<<< orphan*/  track_deform_scale; int /*<<< orphan*/  track_deform_angle; } ;
struct TYPE_42__ {float width; float height; } ;
struct TYPE_41__ {double var_thres; int count; scalar_t__ ferns_thres; TYPE_4__** sv; TYPE_30__ params; TYPE_4__* top; TYPE_8__* ferns; scalar_t__ fern_buffer; scalar_t__ dsfmt; scalar_t__ sfmt; TYPE_26__ patch; } ;
typedef  TYPE_1__ ccv_tld_t ;
struct TYPE_43__ {int /*<<< orphan*/  rows; int /*<<< orphan*/  cols; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;
struct TYPE_47__ {int width; int height; float x; float y; } ;
struct TYPE_45__ {int neighbors; TYPE_6__ rect; } ;
typedef  TYPE_3__ ccv_comp_t ;
struct TYPE_46__ {int rnum; int rsize; } ;
typedef  TYPE_4__ ccv_array_t ;
struct TYPE_48__ {int structs; scalar_t__ threshold; } ;

/* Variables and functions */
 scalar_t__ _ccv_tld_box_variance (TYPE_2__*,TYPE_2__*,TYPE_6__) ; 
 int /*<<< orphan*/  _ccv_tld_ferns_feature_for (TYPE_8__*,TYPE_2__*,TYPE_3__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_tld_fetch_patch (TYPE_1__*,TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ ,TYPE_6__) ; 
 TYPE_3__ _ccv_tld_generate_box_for (int /*<<< orphan*/ ,TYPE_26__,TYPE_6__,int,TYPE_4__**,TYPE_4__**,TYPE_30__) ; 
 scalar_t__ _ccv_tld_rect_intersect (TYPE_6__,TYPE_6__) ; 
 float _ccv_tld_sv_classify (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ _ccv_tld_sv_correct (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (int*) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_4__*) ; 
 int* ccv_array_get (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ccv_ferns_correct (TYPE_8__*,int*,int,int) ; 
 scalar_t__ ccv_ferns_predict (TYPE_8__*,int*) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_2__*) ; 
 TYPE_6__ ccv_rect (int,int,int,int) ; 
 int /*<<< orphan*/  ccv_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double ccv_variance (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  sfmt_genrand_shuffle (int /*<<< orphan*/ *,int*,int,int) ; 
 float sqrtf (float) ; 

__attribute__((used)) static int _ccv_tld_quick_learn(ccv_tld_t* tld, ccv_dense_matrix_t* ga, ccv_dense_matrix_t* sat, ccv_dense_matrix_t* sqsat, ccv_comp_t dd)
{
	ccv_dense_matrix_t* b = 0;
	float scale = sqrtf((float)(dd.rect.width * dd.rect.height) / (tld->patch.width * tld->patch.height));
	// regularize the rect to conform patch's aspect ratio
	dd.rect = ccv_rect((int)(dd.rect.x + (dd.rect.width - tld->patch.width * scale) + 0.5),
					   (int)(dd.rect.y + (dd.rect.height - tld->patch.height * scale) + 0.5),
					   (int)(tld->patch.width * scale + 0.5),
					   (int)(tld->patch.height * scale + 0.5));
	_ccv_tld_fetch_patch(tld, ga, &b, 0, dd.rect);
	double variance = ccv_variance(b);
	int anyp, anyn;
	float c = _ccv_tld_sv_classify(tld, b, 0, 0, &anyp, &anyn);
	ccv_matrix_free(b);
	if (c > tld->params.nnc_collect && !anyn && variance > tld->var_thres)
	{
		ccv_array_t* good = 0;
		ccv_array_t* bad = 0;
		ccv_comp_t best_box = _ccv_tld_generate_box_for(ccv_size(ga->cols, ga->rows), tld->patch, dd.rect, 10, &good, &bad, tld->params);
		int i, j, k = good->rnum;
		// inflate good boxes to take into account deformations
		for (i = 0; i < tld->params.track_deform; i++)
			for (j = 0; j < k; j++)
			{
				// needs to get it out first, otherwise the pointer may be invalid
				// soon (when we realloc the array in push).
				ccv_comp_t box = *(ccv_comp_t*)ccv_array_get(good, j);
				ccv_array_push(good, &box);
			}
		sfmt_t* sfmt = (sfmt_t*)tld->sfmt;
		sfmt_genrand_shuffle(sfmt, ccv_array_get(bad, 0), bad->rnum, bad->rsize);
		int badex = (bad->rnum * 4 + 3) / 6; // only use 2 / 3 bad example for quick learn
		int* idx = (int*)ccmalloc(sizeof(int) * (badex + good->rnum));
		for (i = 0; i < badex + good->rnum; i++)
			idx[i] = i;
		sfmt_genrand_shuffle(sfmt, idx, badex + good->rnum, sizeof(int));
		dsfmt_t* dsfmt = (dsfmt_t*)tld->dsfmt;
		uint32_t* fern = (uint32_t*)ccmalloc(sizeof(uint32_t) * tld->ferns->structs * (badex + 1));
		int r0 = tld->count % (tld->params.rotation + 1), r1 = tld->params.rotation + 1;
		// train the fern classifier
		for (i = 0; i < 2; i++) // run it twice to take into account the cases we missed when warm up
		{
			uint32_t* pfern = fern + tld->ferns->structs;
			for (j = 0; j < badex + good->rnum; j++)
			{
				k = idx[j];
				if (k < badex)
				{
					ccv_comp_t *box = (ccv_comp_t*)ccv_array_get(bad, k);
					if (i == 0)
					{
						assert(box->neighbors >= 0 && box->neighbors < best_box.neighbors);
						if (box->neighbors % r1 == r0 &&
							_ccv_tld_box_variance(sat, sqsat, box->rect) > tld->var_thres)
						{
							// put them in order for faster access the next round
							memcpy(pfern, tld->fern_buffer + box->neighbors * tld->ferns->structs, sizeof(uint32_t) * tld->ferns->structs);
							// fix the thresholding for negative
							if (ccv_ferns_predict(tld->ferns, pfern) >= tld->ferns->threshold)
								ccv_ferns_correct(tld->ferns, pfern, 0, 2); // just feel like to use 2
							pfern += tld->ferns->structs;
						} else
							box->neighbors = -1;
					} else {
						if (box->neighbors < 0)
							continue;
						if (ccv_ferns_predict(tld->ferns, pfern) >= tld->ferns->threshold)
							ccv_ferns_correct(tld->ferns, pfern, 0, 2); // just feel like to use 2
						pfern += tld->ferns->structs;
					}
				} else {
					ccv_comp_t *box = (ccv_comp_t*)ccv_array_get(good, k - badex);
					_ccv_tld_ferns_feature_for(tld->ferns, ga, *box, fern, dsfmt, tld->params.track_deform_angle, tld->params.track_deform_scale, tld->params.track_deform_shift);
					// fix the thresholding for positive
					if (ccv_ferns_predict(tld->ferns, fern) <= tld->ferns_thres)
						ccv_ferns_correct(tld->ferns, fern, 1, 1);
				}
			}
		}
		ccfree(fern);
		ccv_array_free(bad);
		ccv_array_free(good);
		ccfree(idx);
		// train the nearest-neighbor classifier
		ccv_dense_matrix_t* b = 0;
		_ccv_tld_fetch_patch(tld, ga, &b, 0, best_box.rect);
		if (_ccv_tld_sv_correct(tld, b, 1) != 0)
			ccv_matrix_free(b);
		for (i = 0; i < tld->top->rnum; i++)
		{
			ccv_comp_t* box = (ccv_comp_t*)ccv_array_get(tld->top, i);
			if (_ccv_tld_rect_intersect(box->rect, best_box.rect) < tld->params.exclude_overlap)
			{
				ccv_dense_matrix_t* b = 0;
				_ccv_tld_fetch_patch(tld, ga, &b, 0, box->rect);
				if (_ccv_tld_sv_correct(tld, b, 0) != 0)
					ccv_matrix_free(b);
			}
		}
		// shuffle them
		sfmt_genrand_shuffle(sfmt, ccv_array_get(tld->sv[0], 0), tld->sv[0]->rnum, sizeof(ccv_dense_matrix_t*));
		sfmt_genrand_shuffle(sfmt, ccv_array_get(tld->sv[1], 0), tld->sv[1]->rnum, sizeof(ccv_dense_matrix_t*));
		return 0;
	}
	return -1;
}