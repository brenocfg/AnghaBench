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
struct TYPE_4__ {int /*<<< orphan*/ * dw_long; int /*<<< orphan*/  dw_ptrsz; } ;
typedef  TYPE_1__ dwarf_t ;

/* Variables and functions */
 int /*<<< orphan*/  TID_LONG ; 
 int /*<<< orphan*/ * tdesc_intr_common (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tdesc_t *
tdesc_intr_long(dwarf_t *dw)
{
	if (dw->dw_long == NULL) {
		dw->dw_long = tdesc_intr_common(dw, TID_LONG, "long",
		    dw->dw_ptrsz);
	}

	return (dw->dw_long);
}