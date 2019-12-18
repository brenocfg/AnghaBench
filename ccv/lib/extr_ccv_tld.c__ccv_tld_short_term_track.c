#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {float min_forward_backward_error; int /*<<< orphan*/  min_eigen; int /*<<< orphan*/  level; int /*<<< orphan*/  win_size; } ;
typedef  TYPE_2__ ccv_tld_param_t ;
struct TYPE_32__ {float width; float height; int x; int y; } ;
typedef  TYPE_3__ ccv_rect_t ;
struct TYPE_33__ {scalar_t__ cols; scalar_t__ rows; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;
struct TYPE_30__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_34__ {TYPE_1__ point; scalar_t__ status; } ;
typedef  TYPE_5__ ccv_decimal_point_with_status_t ;
struct TYPE_35__ {float x; float y; } ;
typedef  TYPE_6__ ccv_decimal_point_t ;
struct TYPE_36__ {scalar_t__ rnum; } ;
typedef  TYPE_7__ ccv_array_t ;

/* Variables and functions */
 int CCV_8U ; 
 int CCV_C1 ; 
 int TLD_GRID_SPARSITY ; 
 int TLD_PATCH_SIZE ; 
 float _ccv_tld_median (float*,int /*<<< orphan*/ ,int) ; 
 float _ccv_tld_norm_cross_correlate (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_7__*) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int) ; 
 TYPE_7__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_7__*,TYPE_6__*) ; 
 int ccv_compute_dense_matrix_size (int,int,int) ; 
 TYPE_6__ ccv_decimal_point (int,int) ; 
 int /*<<< orphan*/  ccv_decimal_slice (TYPE_4__*,TYPE_4__**,int /*<<< orphan*/ ,float,float,int,int) ; 
 TYPE_4__* ccv_dense_matrix_new (int,int,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_optical_flow_lucas_kanade (TYPE_4__*,TYPE_4__*,TYPE_7__*,TYPE_7__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ccv_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float sqrtf (int) ; 

__attribute__((used)) static ccv_rect_t _ccv_tld_short_term_track(ccv_dense_matrix_t* a, ccv_dense_matrix_t* b, ccv_rect_t box, ccv_tld_param_t params)
{
	ccv_rect_t newbox = ccv_rect(0, 0, 0, 0);
	ccv_array_t* point_a = ccv_array_new(sizeof(ccv_decimal_point_t), (TLD_GRID_SPARSITY - 1) * (TLD_GRID_SPARSITY - 1), 0);
	float gapx = (float)box.width / TLD_GRID_SPARSITY;
	float gapy = (float)box.height / TLD_GRID_SPARSITY;
	float x, y;
	for (x = gapx * 0.5; x < box.width; x += gapx)
		for (y = gapy * 0.5; y < box.height; y += gapy)
		{
			ccv_decimal_point_t point = ccv_decimal_point(box.x + x, box.y + y);
			ccv_array_push(point_a, &point);
		}
	if (point_a->rnum <= 0)
	{
		ccv_array_free(point_a);
		return newbox;
	}
	ccv_array_t* point_b = 0;
	ccv_optical_flow_lucas_kanade(a, b, point_a, &point_b, params.win_size, params.level, params.min_eigen);
	if (point_b->rnum <= 0)
	{
		ccv_array_free(point_b);
		ccv_array_free(point_a);
		return newbox;
	}
	ccv_array_t* point_c = 0;
	ccv_optical_flow_lucas_kanade(b, a, point_b, &point_c, params.win_size, params.level, params.min_eigen);
	// compute forward-backward error
	ccv_dense_matrix_t* r0 = (ccv_dense_matrix_t*)alloca(ccv_compute_dense_matrix_size(TLD_PATCH_SIZE, TLD_PATCH_SIZE, CCV_8U | CCV_C1));
	ccv_dense_matrix_t* r1 = (ccv_dense_matrix_t*)alloca(ccv_compute_dense_matrix_size(TLD_PATCH_SIZE, TLD_PATCH_SIZE, CCV_8U | CCV_C1));
	r0 = ccv_dense_matrix_new(TLD_PATCH_SIZE, TLD_PATCH_SIZE, CCV_8U | CCV_C1, r0, 0);
	r1 = ccv_dense_matrix_new(TLD_PATCH_SIZE, TLD_PATCH_SIZE, CCV_8U | CCV_C1, r1, 0);
	int i, j, k, size;
	int* wrt = (int*)alloca(sizeof(int) * point_a->rnum);
	{ // will reclaim the stack
	float* fberr = (float*)alloca(sizeof(float) * point_a->rnum);
	float* sim = (float*)alloca(sizeof(float) * point_a->rnum);
	for (i = 0, k = 0; i < point_a->rnum; i++)
	{
		ccv_decimal_point_t* p0 = (ccv_decimal_point_t*)ccv_array_get(point_a, i);
		ccv_decimal_point_with_status_t* p1 = (ccv_decimal_point_with_status_t*)ccv_array_get(point_b, i);
		ccv_decimal_point_with_status_t* p2 = (ccv_decimal_point_with_status_t*)ccv_array_get(point_c, i);
		if (p1->status && p2->status &&
			p1->point.x >= 0 && p1->point.x < a->cols && p1->point.y >= 0 && p1->point.y < a->rows &&
			p2->point.x >= 0 && p2->point.x < a->cols && p2->point.y >= 0 && p2->point.y < a->rows)
		{
			fberr[k] = (p2->point.x - p0->x) * (p2->point.x - p0->x) + (p2->point.y - p0->y) * (p2->point.y - p0->y);
			ccv_decimal_slice(a, &r0, 0, p0->y - (TLD_PATCH_SIZE - 1) * 0.5, p0->x - (TLD_PATCH_SIZE - 1) * 0.5, TLD_PATCH_SIZE, TLD_PATCH_SIZE);
			ccv_decimal_slice(b, &r1, 0, p1->point.y - (TLD_PATCH_SIZE - 1) * 0.5, p1->point.x - (TLD_PATCH_SIZE - 1) * 0.5, TLD_PATCH_SIZE, TLD_PATCH_SIZE);
			sim[k] = _ccv_tld_norm_cross_correlate(r0, r1);
			wrt[k] = i;
			++k;
		}
	}
	ccv_array_free(point_c);
	if (k == 0)
	{
		// early termination because we don't have qualified tracking points
		ccv_array_free(point_b);
		ccv_array_free(point_a);
		return newbox;
	}
	size = k;
	float simmd = _ccv_tld_median(sim, 0, size - 1);
	for (i = 0, k = 0; i < size; i++)
		if (sim[i] > simmd)
		{
			fberr[k] = fberr[i];
			wrt[k] = wrt[i];
			++k;
		}
	size = k;
	float fberrmd = _ccv_tld_median(fberr, 0, size - 1);
	if (fberrmd >= params.min_forward_backward_error)
	{
		// early termination because we don't have qualified tracking points
		ccv_array_free(point_b);
		ccv_array_free(point_a);
		return newbox;
	}
	size = k;
	for (i = 0, k = 0; i < size; i++)
		if (fberr[i] <= fberrmd)
			wrt[k++] = wrt[i];
	size = k;
	if (k == 0)
	{
		// early termination because we don't have qualified tracking points
		ccv_array_free(point_b);
		ccv_array_free(point_a);
		return newbox;
	}
	} // reclaim stack
	float dx, dy;
	{ // will reclaim the stack
	float* offx = (float*)alloca(sizeof(float) * size);
	float* offy = (float*)alloca(sizeof(float) * size);
	for (i = 0; i < size; i++)
	{
		ccv_decimal_point_t* p0 = (ccv_decimal_point_t*)ccv_array_get(point_a, wrt[i]);
		ccv_decimal_point_t* p1 = (ccv_decimal_point_t*)ccv_array_get(point_b, wrt[i]);
		offx[i] = p1->x - p0->x;
		offy[i] = p1->y - p0->y;
	}
	dx = _ccv_tld_median(offx, 0, size - 1);
	dy = _ccv_tld_median(offy, 0, size - 1);
	} // reclaim stack
	if (size > 1)
	{
		float* s = (float*)alloca(sizeof(float) * size * (size - 1) / 2);
		k = 0;
		for (i = 0; i < size - 1; i++)
		{
			ccv_decimal_point_t* p0i = (ccv_decimal_point_t*)ccv_array_get(point_a, wrt[i]);
			ccv_decimal_point_t* p1i = (ccv_decimal_point_t*)ccv_array_get(point_b, wrt[i]);
			for (j = i + 1; j < size; j++)
			{
				ccv_decimal_point_t* p0j = (ccv_decimal_point_t*)ccv_array_get(point_a, wrt[j]);
				ccv_decimal_point_t* p1j = (ccv_decimal_point_t*)ccv_array_get(point_b, wrt[j]);
				s[k] = sqrtf(((p1i->x - p1j->x) * (p1i->x - p1j->x) + (p1i->y - p1j->y) * (p1i->y - p1j->y)) /
							 ((p0i->x - p0j->x) * (p0i->x - p0j->x) + (p0i->y - p0j->y) * (p0i->y - p0j->y)));
				++k;
			}
		}
		assert(size * (size - 1) / 2 == k);
		float ds = _ccv_tld_median(s, 0, size * (size - 1) / 2 - 1);
		newbox.x = (int)(box.x + dx - box.width * (ds - 1.0) * 0.5 + 0.5);
		newbox.y = (int)(box.y + dy - box.height * (ds - 1.0) * 0.5 + 0.5);
		newbox.width = (int)(box.width * ds + 0.5);
		newbox.height = (int)(box.height * ds + 0.5);
	} else {
		newbox.width = box.width;
		newbox.height = box.height;
		newbox.x = (int)(box.x + dx + 0.5);
		newbox.y = (int)(box.y + dy + 0.5);
	}
	ccv_array_free(point_b);
	ccv_array_free(point_a);
	return newbox;
}