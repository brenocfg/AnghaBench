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
struct smb_sb_info {scalar_t__ state; scalar_t__ rstate; int /*<<< orphan*/  xmitq; } ;

/* Variables and functions */
 void* CONN_INVALID ; 
 scalar_t__ CONN_VALID ; 
 int /*<<< orphan*/  SMBIOD_DATA_READY ; 
 scalar_t__ SMB_RECV_REQUEST ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ smb_recv_available (struct smb_sb_info*) ; 
 int smb_request_recv (struct smb_sb_info*) ; 
 int smb_request_send_server (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smbiod_flags ; 
 int /*<<< orphan*/  smbiod_handle_request (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smbiod_retry (struct smb_sb_info*) ; 

__attribute__((used)) static void smbiod_doio(struct smb_sb_info *server)
{
	int result;
	int maxwork = 7;

	if (server->state != CONN_VALID)
		goto out;

	do {
		result = smb_request_recv(server);
		if (result < 0) {
			server->state = CONN_INVALID;
			smbiod_retry(server);
			goto out;	/* reconnecting is slow */
		} else if (server->rstate == SMB_RECV_REQUEST)
			smbiod_handle_request(server);
	} while (result > 0 && maxwork-- > 0);

	/*
	 * If there is more to read then we want to be sure to wake up again.
	 */
	if (server->state != CONN_VALID)
		goto out;
	if (smb_recv_available(server) > 0)
		set_bit(SMBIOD_DATA_READY, &smbiod_flags);

	do {
		result = smb_request_send_server(server);
		if (result < 0) {
			server->state = CONN_INVALID;
			smbiod_retry(server);
			goto out;	/* reconnecting is slow */
		}
	} while (result > 0);

	/*
	 * If the last request was not sent out we want to wake up again.
	 */
	if (!list_empty(&server->xmitq))
		set_bit(SMBIOD_DATA_READY, &smbiod_flags);

out:
	return;
}