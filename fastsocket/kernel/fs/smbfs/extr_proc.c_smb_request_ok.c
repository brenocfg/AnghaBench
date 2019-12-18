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
struct smb_request {int rq_resp_wct; int rq_resp_bcc; int /*<<< orphan*/  rq_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*) ; 
 int /*<<< orphan*/  PARANOIA (char*) ; 
 int smb_add_request (struct smb_request*) ; 
 scalar_t__ smb_valid_packet (int /*<<< orphan*/ ) ; 
 int smb_verify (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
smb_request_ok(struct smb_request *req, int command, int wct, int bcc)
{
	int result;

	req->rq_resp_wct = wct;
	req->rq_resp_bcc = bcc;

	result = smb_add_request(req);
	if (result != 0) {
		DEBUG1("smb_request failed\n");
		goto out;
	}

	if (smb_valid_packet(req->rq_header) != 0) {
		PARANOIA("invalid packet!\n");
		goto out;
	}

	result = smb_verify(req->rq_header, command, wct, bcc);

out:
	return result;
}