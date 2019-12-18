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
struct TYPE_5__ {TYPE_2__* t_ardef; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  equiv_data_t ;
struct TYPE_6__ {scalar_t__ ad_nelems; int /*<<< orphan*/  ad_idxtype; int /*<<< orphan*/  ad_contents; } ;
typedef  TYPE_2__ ardef_t ;

/* Variables and functions */
 int /*<<< orphan*/  equiv_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
equiv_array(tdesc_t *stdp, tdesc_t *ttdp, equiv_data_t *ed)
{
	ardef_t *ar1 = stdp->t_ardef, *ar2 = ttdp->t_ardef;

	if (!equiv_node(ar1->ad_contents, ar2->ad_contents, ed) ||
	    !equiv_node(ar1->ad_idxtype, ar2->ad_idxtype, ed))
		return (0);

	if (ar1->ad_nelems != ar2->ad_nelems)
		return (0);

	return (1);
}