#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  msgBusOverflow; } ;
struct vfe_message {TYPE_1__ _u; int /*<<< orphan*/  _d; } ;
struct TYPE_4__ {int /*<<< orphan*/  vfePmData; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VFE_MSG_ID_BUS_OVERFLOW ; 
 TYPE_2__* ctrl ; 
 struct vfe_message* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfe_proc_ops (int /*<<< orphan*/ ,struct vfe_message*,int) ; 

__attribute__((used)) static void vfe_send_bus_overflow_msg(void)
{
	struct vfe_message *msg;
	msg =
		kzalloc(sizeof(struct vfe_message), GFP_ATOMIC);
	if (!msg)
		return;

	msg->_d = VFE_MSG_ID_BUS_OVERFLOW;
#if 0
	memcpy(&(msg->_u.msgBusOverflow),
		&ctrl->vfePmData, sizeof(ctrl->vfePmData));
#endif

	vfe_proc_ops(VFE_MSG_ID_BUS_OVERFLOW,
		msg, sizeof(struct vfe_message));
}