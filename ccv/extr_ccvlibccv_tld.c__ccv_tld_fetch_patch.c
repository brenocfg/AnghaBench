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
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_7__ {TYPE_1__ patch; } ;
typedef  TYPE_2__ ccv_tld_t ;
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
typedef  TYPE_3__ ccv_rect_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_INTER_AREA ; 
 int CCV_INTER_CUBIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_matrix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_resample (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ccv_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void _ccv_tld_fetch_patch(ccv_tld_t* tld, ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, int type, ccv_rect_t box)
{
	if (box.width == tld->patch.width && box.height == tld->patch.height)
		ccv_slice(a, (ccv_matrix_t**)b, type, box.y, box.x, box.height, box.width);
	else {
		assert((box.width >= tld->patch.width && box.height >= tld->patch.height) ||
			   (box.width <= tld->patch.width && box.height <= tld->patch.height));
		ccv_dense_matrix_t* c = 0;
		ccv_slice(a, (ccv_matrix_t**)&c, type, box.y, box.x, box.height, box.width);
		ccv_resample(c, b, type, tld->patch.height, tld->patch.width, CCV_INTER_AREA | CCV_INTER_CUBIC);
		ccv_matrix_free(c);
	}
}