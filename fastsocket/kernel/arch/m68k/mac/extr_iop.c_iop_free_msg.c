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
struct iop_msg {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_MSGSTATUS_UNUSED ; 

__attribute__((used)) static void iop_free_msg(struct iop_msg *msg)
{
	msg->status = IOP_MSGSTATUS_UNUSED;
}