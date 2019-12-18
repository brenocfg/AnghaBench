#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmtp_session {int /*<<< orphan*/  wait; } ;
struct cmtp_application {scalar_t__ state; int err; int /*<<< orphan*/  msgnum; } ;
struct TYPE_4__ {int nbchannel; } ;
struct capi_ctr {TYPE_1__ profile; struct cmtp_session* driverdata; } ;
struct TYPE_5__ {int level3cnt; int datablkcnt; int datablklen; } ;
typedef  TYPE_2__ capi_register_params ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct capi_ctr*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  CAPI_FUNCTION_REGISTER ; 
 int /*<<< orphan*/  CAPI_REQ ; 
 unsigned long CMTP_INTEROP_TIMEOUT ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capimsg_setu16 (unsigned char*,int,int) ; 
 struct cmtp_application* cmtp_application_add (struct cmtp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_application_del (struct cmtp_session*,struct cmtp_application*) ; 
 int /*<<< orphan*/  cmtp_msgnum_get (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_send_interopmsg (struct cmtp_session*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void cmtp_register_appl(struct capi_ctr *ctrl, __u16 appl, capi_register_params *rp)
{
	DECLARE_WAITQUEUE(wait, current);
	struct cmtp_session *session = ctrl->driverdata;
	struct cmtp_application *application;
	unsigned long timeo = CMTP_INTEROP_TIMEOUT;
	unsigned char buf[8];
	int err = 0, nconn, want = rp->level3cnt;

	BT_DBG("ctrl %p appl %d level3cnt %d datablkcnt %d datablklen %d",
		ctrl, appl, rp->level3cnt, rp->datablkcnt, rp->datablklen);

	application = cmtp_application_add(session, appl);
	if (!application) {
		BT_ERR("Can't allocate memory for new application");
		return;
	}

	if (want < 0)
		nconn = ctrl->profile.nbchannel * -want;
	else
		nconn = want;

	if (nconn == 0)
		nconn = ctrl->profile.nbchannel;

	capimsg_setu16(buf, 0, nconn);
	capimsg_setu16(buf, 2, rp->datablkcnt);
	capimsg_setu16(buf, 4, rp->datablklen);

	application->state = BT_CONFIG;
	application->msgnum = cmtp_msgnum_get(session);

	cmtp_send_interopmsg(session, CAPI_REQ, 0x0000, application->msgnum,
				CAPI_FUNCTION_REGISTER, buf, 6);

	add_wait_queue(&session->wait, &wait);
	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (!timeo) {
			err = -EAGAIN;
			break;
		}

		if (application->state == BT_CLOSED) {
			err = -application->err;
			break;
		}

		if (application->state == BT_CONNECTED)
			break;

		if (signal_pending(current)) {
			err = -EINTR;
			break;
		}

		timeo = schedule_timeout(timeo);
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&session->wait, &wait);

	if (err) {
		cmtp_application_del(session, application);
		return;
	}
}