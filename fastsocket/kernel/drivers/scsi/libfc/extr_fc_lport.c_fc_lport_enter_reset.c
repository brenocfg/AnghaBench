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
struct fc_lport {scalar_t__ state; scalar_t__ link_up; int /*<<< orphan*/  host; scalar_t__ vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCH_EVT_LIPRESET ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_VPORT_INITIALIZING ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 scalar_t__ LPORT_ST_DISABLED ; 
 scalar_t__ LPORT_ST_LOGO ; 
 int /*<<< orphan*/  LPORT_ST_RESET ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lport_enter_flogi (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_reset_locked (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_vport_set_state (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_vports_linkchange (struct fc_lport*) ; 

__attribute__((used)) static void fc_lport_enter_reset(struct fc_lport *lport)
{
	FC_LPORT_DBG(lport, "Entered RESET state from %s state\n",
		     fc_lport_state(lport));

	if (lport->state == LPORT_ST_DISABLED || lport->state == LPORT_ST_LOGO)
		return;

	if (lport->vport) {
		if (lport->link_up)
			fc_vport_set_state(lport->vport, FC_VPORT_INITIALIZING);
		else
			fc_vport_set_state(lport->vport, FC_VPORT_LINKDOWN);
	}
	fc_lport_state_enter(lport, LPORT_ST_RESET);
	fc_host_post_event(lport->host, fc_get_event_number(),
			   FCH_EVT_LIPRESET, 0);
	fc_vports_linkchange(lport);
	fc_lport_reset_locked(lport);
	if (lport->link_up)
		fc_lport_enter_flogi(lport);
}