#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdtrav_data_t ;
struct TYPE_6__ {TYPE_1__* iib_td; int /*<<< orphan*/ * iib_tdtd; } ;
typedef  TYPE_2__ iiburst_t ;
struct TYPE_5__ {int /*<<< orphan*/  td_iihash; int /*<<< orphan*/  td_curvgen; } ;

/* Variables and functions */
 int /*<<< orphan*/  burst_iitypes ; 
 int /*<<< orphan*/  burst_types_cbs ; 
 int /*<<< orphan*/  hash_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  tdtrav_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
iiburst_types(iiburst_t *iiburst)
{
	tdtrav_data_t tdtd;

	tdtrav_init(&tdtd, &iiburst->iib_td->td_curvgen, NULL, burst_types_cbs,
	    NULL, (void *)iiburst);

	iiburst->iib_tdtd = &tdtd;

	(void) hash_iter(iiburst->iib_td->td_iihash, burst_iitypes, iiburst);
}