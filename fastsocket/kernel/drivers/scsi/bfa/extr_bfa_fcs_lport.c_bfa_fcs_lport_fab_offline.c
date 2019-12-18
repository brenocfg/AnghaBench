#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfa_fcs_lport_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_lport_ms_offline (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_offline (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_offline (struct bfa_fcs_lport_s*) ; 

__attribute__((used)) static void
bfa_fcs_lport_fab_offline(struct bfa_fcs_lport_s *port)
{
	bfa_fcs_lport_ns_offline(port);
	bfa_fcs_lport_scn_offline(port);
	bfa_fcs_lport_ms_offline(port);
}