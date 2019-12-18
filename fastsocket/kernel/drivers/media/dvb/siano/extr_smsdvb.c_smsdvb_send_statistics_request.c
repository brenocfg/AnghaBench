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
struct smsdvb_client_t {int /*<<< orphan*/  tune_done; } ;
struct SmsMsgHdr_ST {int member_3; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  Msg ;

/* Variables and functions */
 int /*<<< orphan*/  DVBT_BDA_CONTROL_MSG_ID ; 
 int /*<<< orphan*/  HIF_TASK ; 
 int /*<<< orphan*/  MSG_SMS_GET_STATISTICS_REQ ; 
 int smsdvb_sendrequest_and_wait (struct smsdvb_client_t*,struct SmsMsgHdr_ST*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsdvb_send_statistics_request(struct smsdvb_client_t *client)
{
	int rc;
	struct SmsMsgHdr_ST Msg = { MSG_SMS_GET_STATISTICS_REQ,
				    DVBT_BDA_CONTROL_MSG_ID,
				    HIF_TASK,
				    sizeof(struct SmsMsgHdr_ST), 0 };

	rc = smsdvb_sendrequest_and_wait(client, &Msg, sizeof(Msg),
					  &client->tune_done);

	return rc;
}