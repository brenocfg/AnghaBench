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
struct brcms_hardware {TYPE_1__* wlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  fastpwrup_dly; } ;

/* Variables and functions */
 scalar_t__ DBGST_ASLEEP ; 
 int /*<<< orphan*/  M_UCODE_DBGST ; 
 int /*<<< orphan*/  SPINWAIT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_b_read_shm (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void brcms_b_wait_for_wake(struct brcms_hardware *wlc_hw)
{
	/* delay before first read of ucode state */
	udelay(40);

	/* wait until ucode is no longer asleep */
	SPINWAIT((brcms_b_read_shm(wlc_hw, M_UCODE_DBGST) ==
		  DBGST_ASLEEP), wlc_hw->wlc->fastpwrup_dly);
}