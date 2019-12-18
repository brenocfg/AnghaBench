#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int structs; } ;
typedef  TYPE_1__ ccv_ferns_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_11__ {int /*<<< orphan*/  rect; } ;
typedef  TYPE_2__ ccv_comp_t ;
struct TYPE_12__ {int rnum; } ;
typedef  TYPE_3__ ccv_array_t ;

/* Variables and functions */
 double _ccv_tld_box_variance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_tld_ferns_feature_for (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 
 float ccv_ferns_predict (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static float _ccv_tld_ferns_compute_threshold(ccv_ferns_t* ferns, float ferns_thres, ccv_dense_matrix_t* ga, ccv_dense_matrix_t* sat, ccv_dense_matrix_t* sqsat, double var_thres, ccv_array_t* bad, int starter)
{
	int i;
	uint32_t* fern = (uint32_t*)alloca(sizeof(uint32_t) * ferns->structs);
	for (i = starter; i < bad->rnum; i++)
	{
		ccv_comp_t* box = (ccv_comp_t*)ccv_array_get(bad, i);
		if (_ccv_tld_box_variance(sat, sqsat, box->rect) > var_thres)
		{
			_ccv_tld_ferns_feature_for(ferns, ga, *box, fern, 0, 0, 0, 0);
			float c = ccv_ferns_predict(ferns, fern);
			if (c > ferns_thres)
				ferns_thres = c;
		}
	}
	return ferns_thres;
}