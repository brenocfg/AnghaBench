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
struct mid_q_entry {int multiRsp; char* resp_buf; int multiEnd; int large_buf; } ;
struct TCP_Server_Info {int large_buf; int /*<<< orphan*/ * smallbuf; int /*<<< orphan*/ * bigbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  cERROR (int,char*) ; 
 scalar_t__ check2ndT2 (char*) ; 
 int coalesce_t2 (char*,char*) ; 
 void dequeue_mid (struct mid_q_entry*,int) ; 

__attribute__((used)) static void
handle_mid(struct mid_q_entry *mid, struct TCP_Server_Info *server,
	   char *buf, int malformed)
{
	if (malformed == 0 && check2ndT2(buf) > 0) {
		mid->multiRsp = true;
		if (mid->resp_buf) {
			/* merge response - fix up 1st*/
			malformed = coalesce_t2(buf, mid->resp_buf);
			if (malformed > 0)
				return;

			/* All parts received or packet is malformed. */
			mid->multiEnd = true;
			return dequeue_mid(mid, malformed);
		}
		if (!server->large_buf) {
			/*FIXME: switch to already allocated largebuf?*/
			cERROR(1, "1st trans2 resp needs bigbuf");
		} else {
			/* Have first buffer */
			mid->resp_buf = buf;
			mid->large_buf = true;
			server->bigbuf = NULL;
		}
		return;
	}
	mid->resp_buf = buf;
	mid->large_buf = server->large_buf;
	/* Was previous buf put in mpx struct for multi-rsp? */
	if (!mid->multiRsp) {
		/* smb buffer will be freed by user thread */
		if (server->large_buf)
			server->bigbuf = NULL;
		else
			server->smallbuf = NULL;
	}
	dequeue_mid(mid, malformed);
}