#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdata_t ;
typedef  int /*<<< orphan*/  iidesc_t ;
struct TYPE_3__ {scalar_t__ iib_nobjts; void* iib_objts; scalar_t__ iib_nfuncs; void* iib_funcs; int /*<<< orphan*/ * iib_td; } ;
typedef  TYPE_1__ iiburst_t ;

/* Variables and functions */
 void* xcalloc (int) ; 

__attribute__((used)) static iiburst_t *
iiburst_new(tdata_t *td, int max)
{
	iiburst_t *iiburst = xcalloc(sizeof (iiburst_t));
	iiburst->iib_td = td;
	iiburst->iib_funcs = xcalloc(sizeof (iidesc_t *) * max);
	iiburst->iib_nfuncs = 0;
	iiburst->iib_objts = xcalloc(sizeof (iidesc_t *) * max);
	iiburst->iib_nobjts = 0;
	return (iiburst);
}