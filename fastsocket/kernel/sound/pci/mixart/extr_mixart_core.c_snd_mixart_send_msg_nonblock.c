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
typedef  int /*<<< orphan*/  u32 ;
struct mixart_msg {int dummy; } ;
struct mixart_mgr {int /*<<< orphan*/  msg_processed; int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int send_msg (struct mixart_mgr*,struct mixart_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_mixart_send_msg_nonblock(struct mixart_mgr *mgr, struct mixart_msg *request)
{
	u32 message_frame;
	unsigned long flags;
	int err;

	/* just send the message (do not mark it as a pending one) */
	spin_lock_irqsave(&mgr->msg_lock, flags);
	err = send_msg(mgr, request, MSG_DEFAULT_SIZE, 0, &message_frame);
	spin_unlock_irqrestore(&mgr->msg_lock, flags);

	/* the answer will be handled by snd_struct mixart_msgasklet()  */
	atomic_inc(&mgr->msg_processed);

	return err;
}