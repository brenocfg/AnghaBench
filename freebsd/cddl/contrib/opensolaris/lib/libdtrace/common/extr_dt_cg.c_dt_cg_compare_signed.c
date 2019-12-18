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
struct TYPE_5__ {int dn_flags; int /*<<< orphan*/  dn_right; int /*<<< orphan*/  dn_left; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  dn ;

/* Variables and functions */
 int DT_NF_SIGNED ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dt_node_is_arith (int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_promote (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
dt_cg_compare_signed(dt_node_t *dnp)
{
	dt_node_t dn;

	if (dt_node_is_string(dnp->dn_left) ||
	    dt_node_is_string(dnp->dn_right))
		return (1); /* strings always compare signed */
	else if (!dt_node_is_arith(dnp->dn_left) ||
	    !dt_node_is_arith(dnp->dn_right))
		return (0); /* non-arithmetic types always compare unsigned */

	bzero(&dn, sizeof (dn));
	dt_node_promote(dnp->dn_left, dnp->dn_right, &dn);
	return (dn.dn_flags & DT_NF_SIGNED);
}