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
struct TYPE_2__ {char* driver_name; int /*<<< orphan*/  cnr; int /*<<< orphan*/  ctr_read_proc; int /*<<< orphan*/  procinfo; int /*<<< orphan*/  send_message; int /*<<< orphan*/  release_appl; int /*<<< orphan*/  register_appl; int /*<<< orphan*/  reset_ctr; int /*<<< orphan*/  load_firmware; int /*<<< orphan*/  name; struct cmtp_session* driverdata; int /*<<< orphan*/  owner; } ;
struct cmtp_session {int ncontroller; int /*<<< orphan*/  num; TYPE_1__ ctrl; int /*<<< orphan*/  name; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*,...) ; 
 int /*<<< orphan*/  CAPI_FUNCTION_GET_MANUFACTURER ; 
 int /*<<< orphan*/  CAPI_FUNCTION_GET_PROFILE ; 
 int /*<<< orphan*/  CAPI_FUNCTION_GET_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CAPI_FUNCTION_GET_VERSION ; 
 int /*<<< orphan*/  CAPI_REQ ; 
 int /*<<< orphan*/  CMTP_INITIAL_MSGNUM ; 
 int /*<<< orphan*/  CMTP_INTEROP_TIMEOUT ; 
 int EBUSY ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ attach_capi_ctr (TYPE_1__*) ; 
 int /*<<< orphan*/  capimsg_setu32 (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmtp_ctr_read_proc ; 
 int /*<<< orphan*/  cmtp_load_firmware ; 
 int /*<<< orphan*/  cmtp_msgnum_get (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_procinfo ; 
 int /*<<< orphan*/  cmtp_register_appl ; 
 int /*<<< orphan*/  cmtp_release_appl ; 
 int /*<<< orphan*/  cmtp_reset_ctr ; 
 int /*<<< orphan*/  cmtp_send_interopmsg (struct cmtp_session*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  cmtp_send_message ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cmtp_attach_device(struct cmtp_session *session)
{
	unsigned char buf[4];
	long ret;

	BT_DBG("session %p", session);

	capimsg_setu32(buf, 0, 0);

	cmtp_send_interopmsg(session, CAPI_REQ, 0xffff, CMTP_INITIAL_MSGNUM,
				CAPI_FUNCTION_GET_PROFILE, buf, 4);

	ret = wait_event_interruptible_timeout(session->wait,
			session->ncontroller, CMTP_INTEROP_TIMEOUT);

	BT_INFO("Found %d CAPI controller(s) on device %s", session->ncontroller, session->name);

	if (!ret)
		return -ETIMEDOUT;

	if (!session->ncontroller)
		return -ENODEV;

	if (session->ncontroller > 1)
		BT_INFO("Setting up only CAPI controller 1");

	session->ctrl.owner      = THIS_MODULE;
	session->ctrl.driverdata = session;
	strcpy(session->ctrl.name, session->name);

	session->ctrl.driver_name   = "cmtp";
	session->ctrl.load_firmware = cmtp_load_firmware;
	session->ctrl.reset_ctr     = cmtp_reset_ctr;
	session->ctrl.register_appl = cmtp_register_appl;
	session->ctrl.release_appl  = cmtp_release_appl;
	session->ctrl.send_message  = cmtp_send_message;

	session->ctrl.procinfo      = cmtp_procinfo;
	session->ctrl.ctr_read_proc = cmtp_ctr_read_proc;

	if (attach_capi_ctr(&session->ctrl) < 0) {
		BT_ERR("Can't attach new controller");
		return -EBUSY;
	}

	session->num = session->ctrl.cnr;

	BT_DBG("session %p num %d", session, session->num);

	capimsg_setu32(buf, 0, 1);

	cmtp_send_interopmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_MANUFACTURER, buf, 4);

	cmtp_send_interopmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_VERSION, buf, 4);

	cmtp_send_interopmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_SERIAL_NUMBER, buf, 4);

	cmtp_send_interopmsg(session, CAPI_REQ, 0xffff, cmtp_msgnum_get(session),
				CAPI_FUNCTION_GET_PROFILE, buf, 4);

	return 0;
}