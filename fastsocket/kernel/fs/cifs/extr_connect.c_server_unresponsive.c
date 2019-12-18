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
struct TCP_Server_Info {scalar_t__ tcpStatus; int /*<<< orphan*/  response_q; int /*<<< orphan*/  hostname; scalar_t__ lstrp; } ;

/* Variables and functions */
 scalar_t__ CifsGood ; 
 int HZ ; 
 int SMB_ECHO_INTERVAL ; 
 int /*<<< orphan*/  cERROR (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cifs_reconnect (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
server_unresponsive(struct TCP_Server_Info *server)
{
	/*
	 * We need to wait 2 echo intervals to make sure we handle such
	 * situations right:
	 * 1s  client sends a normal SMB request
	 * 2s  client gets a response
	 * 30s echo workqueue job pops, and decides we got a response recently
	 *     and don't need to send another
	 * ...
	 * 65s kernel_recvmsg times out, and we see that we haven't gotten
	 *     a response in >60s.
	 */
	if (server->tcpStatus == CifsGood &&
	    time_after(jiffies, server->lstrp + 2 * SMB_ECHO_INTERVAL)) {
		cERROR(1, "Server %s has not responded in %d seconds. "
			  "Reconnecting...", server->hostname,
			  (2 * SMB_ECHO_INTERVAL) / HZ);
		cifs_reconnect(server);
		wake_up(&server->response_q);
		return true;
	}

	return false;
}