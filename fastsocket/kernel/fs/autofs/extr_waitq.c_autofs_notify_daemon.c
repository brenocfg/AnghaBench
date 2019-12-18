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
struct autofs_wait_queue {size_t len; int /*<<< orphan*/  name; int /*<<< orphan*/  wait_queue_token; } ;
struct autofs_sb_info {int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  proto_version; } ;
struct autofs_packet_missing {size_t len; char* name; int /*<<< orphan*/  wait_queue_token; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_PROTO_VERSION ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs_catatonic_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs_ptype_missing ; 
 int /*<<< orphan*/  autofs_say (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ autofs_write (int /*<<< orphan*/ ,struct autofs_packet_missing*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (struct autofs_packet_missing*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void autofs_notify_daemon(struct autofs_sb_info *sbi, struct autofs_wait_queue *wq)
{
	struct autofs_packet_missing pkt;

	DPRINTK(("autofs_wait: wait id = 0x%08lx, name = ", wq->wait_queue_token));
	autofs_say(wq->name,wq->len);

	memset(&pkt,0,sizeof pkt); /* For security reasons */

	pkt.hdr.proto_version = AUTOFS_PROTO_VERSION;
	pkt.hdr.type = autofs_ptype_missing;
	pkt.wait_queue_token = wq->wait_queue_token;
	pkt.len = wq->len;
        memcpy(pkt.name, wq->name, pkt.len);
	pkt.name[pkt.len] = '\0';

	if ( autofs_write(sbi->pipe,&pkt,sizeof(struct autofs_packet_missing)) )
		autofs_catatonic_mode(sbi);
}