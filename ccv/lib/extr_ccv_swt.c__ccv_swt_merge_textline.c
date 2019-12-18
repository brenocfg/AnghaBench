#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int width; int height; } ;
struct TYPE_23__ {int dx; int dy; scalar_t__ neighbors; struct TYPE_23__* letters; TYPE_2__ rect; TYPE_5__* right; TYPE_5__* left; } ;
typedef  TYPE_3__ ccv_textline_t ;
struct TYPE_24__ {double thickness_ratio; double height_ratio; int intensity_thresh; int distance_ratio; int intersect_ratio; scalar_t__ letter_thresh; int elongate_ratio; } ;
typedef  TYPE_4__ ccv_swt_param_t ;
struct TYPE_21__ {double height; int x; int width; int y; } ;
struct TYPE_25__ {double thickness; int intensity; TYPE_1__ rect; } ;
typedef  TYPE_5__ ccv_letter_t ;
typedef  TYPE_3__ ccv_letter_pair_t ;
struct TYPE_26__ {int rnum; } ;
typedef  TYPE_7__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_in_textline ; 
 int /*<<< orphan*/  _ccv_swt_add_letter (TYPE_3__*,TYPE_5__*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  ccfree (TYPE_3__*) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_7__*) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int) ; 
 int ccv_array_group (TYPE_7__*,TYPE_7__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_7__*,TYPE_3__*) ; 
 int ccv_max (int,int) ; 
 int ccv_min (int,int) ; 

__attribute__((used)) static ccv_array_t* _ccv_swt_merge_textline(ccv_array_t* letters, ccv_swt_param_t params)
{
	int i, j;
	ccv_array_t* pairs = ccv_array_new(sizeof(ccv_letter_pair_t), letters->rnum, 0);
	double thickness_ratio_inv = 1.0 / params.thickness_ratio;
	double height_ratio_inv = 1.0 / params.height_ratio;
	for (i = 0; i < letters->rnum - 1; i++)
	{
		ccv_letter_t* li = (ccv_letter_t*)ccv_array_get(letters, i);
		for (j = i + 1; j < letters->rnum; j++)
		{
			ccv_letter_t* lj = (ccv_letter_t*)ccv_array_get(letters, j);
			double ratio = (double)li->thickness / lj->thickness;
			if (ratio > params.thickness_ratio || ratio < thickness_ratio_inv)
				continue;
			ratio = (double)li->rect.height / lj->rect.height;
			if (ratio > params.height_ratio || ratio < height_ratio_inv)
				continue;
			if (abs(li->intensity - lj->intensity) > params.intensity_thresh)
				continue;
			int dx = li->rect.x - lj->rect.x + (li->rect.width - lj->rect.width) / 2;
			int dy = li->rect.y - lj->rect.y + (li->rect.height - lj->rect.height) / 2;
			if (abs(dx) > params.distance_ratio * ccv_max(li->rect.width, lj->rect.width))
				continue;
			int oy = ccv_min(li->rect.y + li->rect.height, lj->rect.y + lj->rect.height) - ccv_max(li->rect.y, lj->rect.y);
			if (oy * params.intersect_ratio < ccv_min(li->rect.height, lj->rect.height))
				continue;
			ccv_letter_pair_t pair = { .left = li, .right = lj, .dx = dx, .dy = dy };
			ccv_array_push(pairs, &pair);
		}
	}
	ccv_array_t* idx = 0;
	int nchains = ccv_array_group(pairs, &idx, _ccv_in_textline, 0);
	ccv_textline_t* chain = (ccv_textline_t*)ccmalloc(nchains * sizeof(ccv_textline_t));
	for (i = 0; i < nchains; i++)
		chain[i].neighbors = 0;
	for (i = 0; i < pairs->rnum; i++)
	{
		j = *(int*)ccv_array_get(idx, i);
		_ccv_swt_add_letter(chain + j,((ccv_letter_pair_t*)ccv_array_get(pairs, i))->left);
		_ccv_swt_add_letter(chain + j, ((ccv_letter_pair_t*)ccv_array_get(pairs, i))->right);
	}
	ccv_array_free(idx);
	ccv_array_free(pairs);
	ccv_array_t* regions = ccv_array_new(sizeof(ccv_textline_t), 5, 0);
	for (i = 0; i < nchains; i++)
		if (chain[i].neighbors >= params.letter_thresh && chain[i].rect.width > chain[i].rect.height * params.elongate_ratio)
			ccv_array_push(regions, chain + i);
		else if (chain[i].neighbors > 0)
			ccfree(chain[i].letters);
	ccfree(chain);
	return regions;
}