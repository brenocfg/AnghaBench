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
typedef  int u32 ;
typedef  scalar_t__ addr_t ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int ext_params; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 TYPE_2__ S390_lowcore ; 
 int /*<<< orphan*/  SCLP_REQ_DONE ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__ sclp_init_req ; 
 scalar_t__ sclp_init_sccb ; 
 int /*<<< orphan*/  sclp_lock ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 scalar_t__ sclp_running_state_running ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sclp_check_handler(__u16 code)
{
	u32 finished_sccb;

	finished_sccb = S390_lowcore.ext_params & 0xfffffff8;
	/* Is this the interrupt we are waiting for? */
	if (finished_sccb == 0)
		return;
	if (finished_sccb != (u32) (addr_t) sclp_init_sccb)
		panic("sclp: unsolicited interrupt for buffer at 0x%x\n",
		      finished_sccb);
	spin_lock(&sclp_lock);
	if (sclp_running_state == sclp_running_state_running) {
		sclp_init_req.status = SCLP_REQ_DONE;
		sclp_running_state = sclp_running_state_idle;
	}
	spin_unlock(&sclp_lock);
}