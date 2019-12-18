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
struct cmtp_session {int /*<<< orphan*/  wait; } ;
struct cmtp_application {scalar_t__ state; int /*<<< orphan*/  msgnum; int /*<<< orphan*/  mapping; } ;
struct capi_ctr {struct cmtp_session* driverdata; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct capi_ctr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  CAPI_FUNCTION_RELEASE ; 
 int /*<<< orphan*/  CAPI_REQ ; 
 int /*<<< orphan*/  CMTP_APPLID ; 
 int /*<<< orphan*/  CMTP_INTEROP_TIMEOUT ; 
 int /*<<< orphan*/  cmtp_application_del (struct cmtp_session*,struct cmtp_application*) ; 
 struct cmtp_application* cmtp_application_get (struct cmtp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_msgnum_get (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_send_interopmsg (struct cmtp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmtp_release_appl(struct capi_ctr *ctrl, __u16 appl)
{
	struct cmtp_session *session = ctrl->driverdata;
	struct cmtp_application *application;

	BT_DBG("ctrl %p appl %d", ctrl, appl);

	application = cmtp_application_get(session, CMTP_APPLID, appl);
	if (!application) {
		BT_ERR("Can't find application");
		return;
	}

	application->msgnum = cmtp_msgnum_get(session);

	cmtp_send_interopmsg(session, CAPI_REQ, application->mapping, application->msgnum,
				CAPI_FUNCTION_RELEASE, NULL, 0);

	wait_event_interruptible_timeout(session->wait,
			(application->state == BT_CLOSED), CMTP_INTEROP_TIMEOUT);

	cmtp_application_del(session, application);
}