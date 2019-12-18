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
typedef  scalar_t__ uint ;
struct iop_msg {int* reply; scalar_t__* message; } ;
struct adb_request {int reply_len; int* reply; } ;
struct adb_iopmsg {int count; int flags; scalar_t__ cmd; scalar_t__* data; } ;

/* Variables and functions */
 int ADB_IOP_AUTOPOLL ; 
 int ADB_IOP_EXPLICIT ; 
 int ADB_IOP_TIMEOUT ; 
 int IOP_MSG_LEN ; 
 int /*<<< orphan*/  adb_input (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  adb_iop_end_req (struct adb_request*,scalar_t__) ; 
 scalar_t__ adb_iop_state ; 
 scalar_t__ awaiting_reply ; 
 struct adb_request* current_req ; 
 scalar_t__ idle ; 
 int /*<<< orphan*/  iop_complete_message (struct iop_msg*) ; 
 int /*<<< orphan*/  local_irq_restore (scalar_t__) ; 
 int /*<<< orphan*/  local_irq_save (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void adb_iop_listen(struct iop_msg *msg)
{
	struct adb_iopmsg *amsg = (struct adb_iopmsg *) msg->message;
	struct adb_request *req;
	uint flags;
#ifdef DEBUG_ADB_IOP
	int i;
#endif

	local_irq_save(flags);

	req = current_req;

#ifdef DEBUG_ADB_IOP
	printk("adb_iop_listen %p: rcvd packet, %d bytes: %02X %02X", req,
		(uint) amsg->count + 2, (uint) amsg->flags, (uint) amsg->cmd);
	for (i = 0; i < amsg->count; i++)
		printk(" %02X", (uint) amsg->data[i]);
	printk("\n");
#endif

	/* Handle a timeout. Timeout packets seem to occur even after */
	/* we've gotten a valid reply to a TALK, so I'm assuming that */
	/* a "timeout" is actually more like an "end-of-data" signal. */
	/* We need to send back a timeout packet to the IOP to shut   */
	/* it up, plus complete the current request, if any.          */

	if (amsg->flags & ADB_IOP_TIMEOUT) {
		msg->reply[0] = ADB_IOP_TIMEOUT | ADB_IOP_AUTOPOLL;
		msg->reply[1] = 0;
		msg->reply[2] = 0;
		if (req && (adb_iop_state != idle)) {
			adb_iop_end_req(req, idle);
		}
	} else {
		/* TODO: is it possible for more than one chunk of data  */
		/*       to arrive before the timeout? If so we need to */
		/*       use reply_ptr here like the other drivers do.  */
		if ((adb_iop_state == awaiting_reply) &&
		    (amsg->flags & ADB_IOP_EXPLICIT)) {
			req->reply_len = amsg->count + 1;
			memcpy(req->reply, &amsg->cmd, req->reply_len);
		} else {
			adb_input(&amsg->cmd, amsg->count + 1,
				  amsg->flags & ADB_IOP_AUTOPOLL);
		}
		memcpy(msg->reply, msg->message, IOP_MSG_LEN);
	}
	iop_complete_message(msg);
	local_irq_restore(flags);
}