#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
struct TYPE_5__ {int /*<<< orphan*/  dr_size; int /*<<< orphan*/ * dr_bitmap; } ;
typedef  TYPE_1__ dt_regset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_BITOUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt_regset_destroy (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

dt_regset_t *
dt_regset_create(ulong_t nregs)
{
	ulong_t n = BT_BITOUL(nregs);
	dt_regset_t *drp = malloc(sizeof (dt_regset_t));

	if (drp == NULL)
		return (NULL);

	drp->dr_bitmap = calloc(n, sizeof (ulong_t));

	if (drp->dr_bitmap == NULL) {
		dt_regset_destroy(drp);
		return (NULL);
	}

	drp->dr_size = nregs;

	return (drp);
}