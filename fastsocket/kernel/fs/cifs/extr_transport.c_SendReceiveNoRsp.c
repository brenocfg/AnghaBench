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
struct kvec {char* iov_base; scalar_t__ iov_len; } ;
struct cifs_ses {int dummy; } ;

/* Variables and functions */
 int CIFS_NO_RESP ; 
 int /*<<< orphan*/  DBG2 ; 
 int SendReceive2 (unsigned int const,struct cifs_ses*,struct kvec*,int,int*,int) ; 
 int /*<<< orphan*/  cFYI (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ get_rfc1002_length (char*) ; 

int
SendReceiveNoRsp(const unsigned int xid, struct cifs_ses *ses,
		 char *in_buf, int flags)
{
	int rc;
	struct kvec iov[1];
	int resp_buf_type;

	iov[0].iov_base = in_buf;
	iov[0].iov_len = get_rfc1002_length(in_buf) + 4;
	flags |= CIFS_NO_RESP;
	rc = SendReceive2(xid, ses, iov, 1, &resp_buf_type, flags);
	cFYI(DBG2, "SendRcvNoRsp flags %d rc %d", flags, rc);

	return rc;
}