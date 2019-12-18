#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdesc_t ;
struct TYPE_4__ {int ii_nargs; int /*<<< orphan*/ * ii_dtype; int /*<<< orphan*/ ** ii_args; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int FUNCARG_DEF ; 
 int /*<<< orphan*/ ** xmalloc (int) ; 
 int /*<<< orphan*/ ** xrealloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
fnarg_add(iidesc_t *curfun, iidesc_t *arg)
{
	curfun->ii_nargs++;

	if (curfun->ii_nargs == 1)
		curfun->ii_args = xmalloc(sizeof (tdesc_t *) * FUNCARG_DEF);
	else if (curfun->ii_nargs > FUNCARG_DEF) {
		curfun->ii_args = xrealloc(curfun->ii_args,
		    sizeof (tdesc_t *) * curfun->ii_nargs);
	}

	curfun->ii_args[curfun->ii_nargs - 1] = arg->ii_dtype;
	arg->ii_dtype = NULL;
}