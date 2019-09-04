#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float nnc_same; } ;
struct TYPE_10__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_12__ {TYPE_2__ params; TYPE_5__** sv; TYPE_1__ patch; } ;
typedef  TYPE_3__ ccv_tld_t ;
struct TYPE_13__ {scalar_t__ rows; scalar_t__ cols; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;
struct TYPE_14__ {int rnum; } ;

/* Variables and functions */
 float _ccv_tld_norm_cross_correlate (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int ccv_min (int,int) ; 

__attribute__((used)) static float _ccv_tld_sv_classify(ccv_tld_t* tld, ccv_dense_matrix_t* a, int pnum, int nnum, int* anyp, int* anyn)
{
	assert(a->rows == tld->patch.height && a->cols == tld->patch.width);
	int i;
	pnum = (pnum <= 0) ? tld->sv[1]->rnum : ccv_min(pnum, tld->sv[1]->rnum);
	if (pnum == 0)
		return 0;
	nnum = (nnum <= 0) ? tld->sv[0]->rnum : ccv_min(nnum, tld->sv[0]->rnum);
	if (nnum == 0)
		return 1;
	float maxp = -1;
	for (i = 0; i < pnum; i++)
	{
		ccv_dense_matrix_t* b = *(ccv_dense_matrix_t**)ccv_array_get(tld->sv[1], i);
		float nnc = _ccv_tld_norm_cross_correlate(a, b);
		if (nnc > maxp)
			maxp = nnc;
	}
	maxp = (maxp + 1) * 0.5; // make it in 0~1 range
	if (anyp)
		*anyp = (maxp > tld->params.nnc_same);
	float maxn = -1;
	for (i = 0; i < nnum; i++)
	{
		ccv_dense_matrix_t* b = *(ccv_dense_matrix_t**)ccv_array_get(tld->sv[0], i);
		float nnc = _ccv_tld_norm_cross_correlate(a, b);
		if (nnc > maxn)
			maxn = nnc;
	}
	maxn = (maxn + 1) * 0.5; // make it in 0~1 range
	if (anyn)
		*anyn = (maxn > tld->params.nnc_same);
	return (1 - maxn) / (2 - maxn - maxp);
}