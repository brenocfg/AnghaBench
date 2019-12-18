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
struct cifs_ses {struct TCP_Server_Info* server; } ;
struct TCP_Server_Info {scalar_t__ maxBuf; scalar_t__ tcpStatus; } ;

/* Variables and functions */
 int CIFSSMBNegotiate (unsigned int,struct cifs_ses*) ; 
 scalar_t__ CifsGood ; 
 scalar_t__ CifsNeedNegotiate ; 
 int EAGAIN ; 
 int EHOSTDOWN ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int /*<<< orphan*/  cifs_set_credits (struct TCP_Server_Info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int cifs_negotiate_protocol(unsigned int xid, struct cifs_ses *ses)
{
	int rc = 0;
	struct TCP_Server_Info *server = ses->server;

	/* only send once per connect */
	if (server->maxBuf != 0)
		return 0;

	cifs_set_credits(server, 1);
	rc = CIFSSMBNegotiate(xid, ses);
	if (rc == -EAGAIN) {
		/* retry only once on 1st time connection */
		cifs_set_credits(server, 1);
		rc = CIFSSMBNegotiate(xid, ses);
		if (rc == -EAGAIN)
			rc = -EHOSTDOWN;
	}
	if (rc == 0) {
		spin_lock(&GlobalMid_Lock);
		if (server->tcpStatus == CifsNeedNegotiate)
			server->tcpStatus = CifsGood;
		else
			rc = -EHOSTDOWN;
		spin_unlock(&GlobalMid_Lock);

	}

	return rc;
}