#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float nnc_thres; float nnc_collect; } ;
struct TYPE_7__ {TYPE_3__** sv; TYPE_1__ params; } ;
typedef  TYPE_2__ ccv_tld_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_8__ {scalar_t__ rnum; } ;

/* Variables and functions */
 float _ccv_tld_sv_classify (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_3__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int _ccv_tld_sv_correct(ccv_tld_t* tld, ccv_dense_matrix_t* a, int y)
{
	int anyp, anyn;
	if (y == 1 && tld->sv[1]->rnum == 0)
	{
		ccv_array_push(tld->sv[1], &a);
		return 0;
	}
	float conf = _ccv_tld_sv_classify(tld, a, 0, 0, &anyp, &anyn);
	if (y == 1 && conf < tld->params.nnc_thres)
	{
		ccv_array_push(tld->sv[1], &a);
		return 0;
	} else if (y == 0 && conf > tld->params.nnc_collect) {
		ccv_array_push(tld->sv[0], &a);
		return 0;
	}
	return -1;
}