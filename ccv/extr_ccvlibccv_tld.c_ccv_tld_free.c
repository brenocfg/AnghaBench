#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ferns; TYPE_3__* top; TYPE_3__** sv; struct TYPE_6__* sfmt; struct TYPE_6__* dsfmt; } ;
typedef  TYPE_1__ ccv_tld_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_7__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_3__*) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ccv_ferns_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (int /*<<< orphan*/ *) ; 

void ccv_tld_free(ccv_tld_t* tld)
{
	int i;
	ccfree(tld->dsfmt);
	ccfree(tld->sfmt);
	for (i = 0; i < tld->sv[0]->rnum; i++)
		ccv_matrix_free(*(ccv_dense_matrix_t**)ccv_array_get(tld->sv[0], i));
	ccv_array_free(tld->sv[0]);
	for (i = 0; i < tld->sv[1]->rnum; i++)
		ccv_matrix_free(*(ccv_dense_matrix_t**)ccv_array_get(tld->sv[1], i));
	ccv_array_free(tld->sv[1]);
	ccv_array_free(tld->top);
	ccv_ferns_free(tld->ferns);
	ccfree(tld);
}