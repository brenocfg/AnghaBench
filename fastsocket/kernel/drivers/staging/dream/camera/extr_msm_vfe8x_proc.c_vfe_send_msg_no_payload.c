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
struct vfe_message {int _d; } ;
typedef  enum VFE_MESSAGE_ID { ____Placeholder_VFE_MESSAGE_ID } VFE_MESSAGE_ID ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct vfe_message* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_proc_ops (int,struct vfe_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_send_msg_no_payload(enum VFE_MESSAGE_ID id)
{
	struct vfe_message *msg;

	msg = kzalloc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		return;

	msg->_d = id;
	vfe_proc_ops(id, msg, 0);
}