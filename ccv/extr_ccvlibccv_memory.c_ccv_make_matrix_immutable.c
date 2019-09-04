#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_3__ {scalar_t__ u8; } ;
struct TYPE_4__ {scalar_t__ sig; int rows; int step; scalar_t__ type; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_EOF_SIGN ; 
 int CCV_MATRIX_DENSE ; 
 scalar_t__ CCV_REUSABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_cache_generate_signature (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ccv_make_matrix_immutable(ccv_matrix_t* mat)
{
	int type = *(int*)mat;
	if (type & CCV_MATRIX_DENSE)
	{
		ccv_dense_matrix_t* dmt = (ccv_dense_matrix_t*)mat;
		assert(dmt->sig == 0); // you cannot make matrix with derived signature immutable (it is immutable already)
		/* immutable matrix made this way is not reusable (collected), because its signature
		 * only depends on the content, not the operation to generate it */
		dmt->type &= ~CCV_REUSABLE;
		dmt->sig = ccv_cache_generate_signature((char*)dmt->data.u8, dmt->rows * dmt->step, (uint64_t)dmt->type, CCV_EOF_SIGN);
	}
}