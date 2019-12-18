#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdtrav_data_t ;
struct TYPE_2__ {int ii_nargs; int /*<<< orphan*/ * ii_args; int /*<<< orphan*/  ii_dtype; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int tdtraverse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
iitraverse_td(void *arg1, void *arg2)
{
	iidesc_t *ii = arg1;
	tdtrav_data_t *tdtd = arg2;
	int i, rc;

	if ((rc = tdtraverse(ii->ii_dtype, &ii->ii_dtype, tdtd)) < 0)
		return (rc);

	for (i = 0; i < ii->ii_nargs; i++) {
		if ((rc = tdtraverse(ii->ii_args[i], &ii->ii_args[i],
		    tdtd)) < 0)
			return (rc);
	}

	return (1);
}