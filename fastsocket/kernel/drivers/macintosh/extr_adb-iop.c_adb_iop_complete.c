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
typedef  int /*<<< orphan*/  uint ;
struct iop_msg {int dummy; } ;
struct adb_request {scalar_t__ reply_expected; } ;

/* Variables and functions */
 scalar_t__ adb_iop_state ; 
 scalar_t__ awaiting_reply ; 
 struct adb_request* current_req ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 
 scalar_t__ sending ; 

__attribute__((used)) static void adb_iop_complete(struct iop_msg *msg)
{
	struct adb_request *req;
	uint flags;

	local_irq_save(flags);

	req = current_req;
	if ((adb_iop_state == sending) && req && req->reply_expected) {
		adb_iop_state = awaiting_reply;
	}

	local_irq_restore(flags);
}