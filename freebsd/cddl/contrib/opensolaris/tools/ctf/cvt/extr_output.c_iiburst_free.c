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
struct TYPE_4__ {int /*<<< orphan*/  iib_types; struct TYPE_4__* iib_objts; struct TYPE_4__* iib_funcs; } ;
typedef  TYPE_1__ iiburst_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iiburst_free(iiburst_t *iiburst)
{
	free(iiburst->iib_funcs);
	free(iiburst->iib_objts);
	list_free(iiburst->iib_types, NULL, NULL);
	free(iiburst);
}