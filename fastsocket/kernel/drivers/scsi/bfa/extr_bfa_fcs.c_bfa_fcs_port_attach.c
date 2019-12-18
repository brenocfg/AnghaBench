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
struct bfa_fcs_s {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcport_event_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_fcs_port_event_handler ; 

void
bfa_fcs_port_attach(struct bfa_fcs_s *fcs)
{
	bfa_fcport_event_register(fcs->bfa, bfa_fcs_port_event_handler, fcs);
}