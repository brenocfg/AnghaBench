#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int version; int length; int /*<<< orphan*/  opcode; } ;
struct ibmvfc_npiv_logout_mad {TYPE_2__ common; } ;
struct ibmvfc_host {int dummy; } ;
struct TYPE_3__ {struct ibmvfc_npiv_logout_mad npiv_logout; } ;
struct ibmvfc_event {TYPE_1__ iu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_LOGO_WAIT ; 
 int /*<<< orphan*/  IBMVFC_LINK_DEAD ; 
 int /*<<< orphan*/  IBMVFC_MAD_FORMAT ; 
 int /*<<< orphan*/  IBMVFC_NPIV_LOGOUT ; 
 int /*<<< orphan*/  default_timeout ; 
 int /*<<< orphan*/  ibmvfc_dbg (struct ibmvfc_host*,char*) ; 
 struct ibmvfc_event* ibmvfc_get_event (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_init_event (struct ibmvfc_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_npiv_logout_done ; 
 int /*<<< orphan*/  ibmvfc_send_event (struct ibmvfc_event*,struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ibmvfc_npiv_logout_mad*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ibmvfc_npiv_logout(struct ibmvfc_host *vhost)
{
	struct ibmvfc_npiv_logout_mad *mad;
	struct ibmvfc_event *evt;

	evt = ibmvfc_get_event(vhost);
	ibmvfc_init_event(evt, ibmvfc_npiv_logout_done, IBMVFC_MAD_FORMAT);

	mad = &evt->iu.npiv_logout;
	memset(mad, 0, sizeof(*mad));
	mad->common.version = 1;
	mad->common.opcode = IBMVFC_NPIV_LOGOUT;
	mad->common.length = sizeof(struct ibmvfc_npiv_logout_mad);

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_LOGO_WAIT);

	if (!ibmvfc_send_event(evt, vhost, default_timeout))
		ibmvfc_dbg(vhost, "Sent NPIV logout\n");
	else
		ibmvfc_link_down(vhost, IBMVFC_LINK_DEAD);
}