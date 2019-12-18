#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct socket {int so_flags; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  last_pid; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  e_pid; } ;
struct kev_netevent_apnfallbk_data {TYPE_1__* dv; int /*<<< orphan*/  euuid; int /*<<< orphan*/  epid; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_msg {TYPE_1__* dv; int /*<<< orphan*/  euuid; int /*<<< orphan*/  epid; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  application_uuid ;
typedef  int /*<<< orphan*/  apnfallbk_data ;
struct TYPE_2__ {int data_length; struct kev_netevent_apnfallbk_data* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_NETEVENT_APNFALLBACK ; 
 int /*<<< orphan*/  KEV_NETEVENT_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SOF_DELEGATED ; 
 int /*<<< orphan*/  apn_fallbk_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct kev_netevent_apnfallbk_data*,int) ; 
 int /*<<< orphan*/  kev_post_msg (struct kev_netevent_apnfallbk_data*) ; 
 int /*<<< orphan*/  last_apn_fallback ; 
 int /*<<< orphan*/  net_uptime () ; 
 int /*<<< orphan*/  proc_getexecutableuuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apn_fallback_trigger(proc_t proc, struct socket *so)
{
	pid_t pid = 0;
	struct kev_msg ev_msg;
	struct kev_netevent_apnfallbk_data apnfallbk_data;

	last_apn_fallback = net_uptime();
	pid = proc_pid(proc);
	uuid_t application_uuid;
	uuid_clear(application_uuid);
	proc_getexecutableuuid(proc, application_uuid,
	    sizeof(application_uuid));

	bzero(&ev_msg, sizeof (struct kev_msg));
	ev_msg.vendor_code      = KEV_VENDOR_APPLE;
	ev_msg.kev_class        = KEV_NETWORK_CLASS;
	ev_msg.kev_subclass     = KEV_NETEVENT_SUBCLASS;
	ev_msg.event_code       = KEV_NETEVENT_APNFALLBACK;

	bzero(&apnfallbk_data, sizeof(apnfallbk_data));

	if (so->so_flags & SOF_DELEGATED) {
		apnfallbk_data.epid = so->e_pid;
		uuid_copy(apnfallbk_data.euuid, so->e_uuid);
	} else {
		apnfallbk_data.epid = so->last_pid;
		uuid_copy(apnfallbk_data.euuid, so->last_uuid);
	}

	ev_msg.dv[0].data_ptr   = &apnfallbk_data;
	ev_msg.dv[0].data_length = sizeof(apnfallbk_data);
	kev_post_msg(&ev_msg);
	apn_fallbk_log((LOG_INFO, "APN fallback notification issued.\n"));
}