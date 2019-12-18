#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  merge_cb_data_t ;
struct TYPE_6__ {int ii_nargs; int /*<<< orphan*/ * ii_args; int /*<<< orphan*/  ii_dtype; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 TYPE_1__* iidesc_dup (TYPE_1__*) ; 
 int /*<<< orphan*/  remap_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static iidesc_t *
conjure_iidesc(iidesc_t *old, merge_cb_data_t *mcd)
{
	iidesc_t *new = iidesc_dup(old);
	int i;

	(void) remap_node(&new->ii_dtype, old->ii_dtype, -1, NULL, mcd);
	for (i = 0; i < new->ii_nargs; i++) {
		(void) remap_node(&new->ii_args[i], old->ii_args[i], -1, NULL,
		    mcd);
	}

	return (new);
}