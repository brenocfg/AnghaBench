#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int apctl_v_agp_present; } ;
union TPAchipPCTL {TYPE_2__ pctl_r_bits; int /*<<< orphan*/  pctl_q_whole; } ;
struct TYPE_5__ {int /*<<< orphan*/  csr; } ;
struct TYPE_7__ {TYPE_1__ pctl; } ;
typedef  TYPE_3__ titan_pachip_port ;

/* Variables and functions */

__attribute__((used)) static int
titan_query_agp(titan_pachip_port *port)
{
	union TPAchipPCTL pctl;

	/* set up APCTL */
	pctl.pctl_q_whole = port->pctl.csr;

	return pctl.pctl_r_bits.apctl_v_agp_present;

}