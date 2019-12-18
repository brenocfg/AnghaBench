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
typedef  int u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
#define  B43_FWPANIC_DIE 129 
 int /*<<< orphan*/  B43_FWPANIC_REASON_REG ; 
#define  B43_FWPANIC_RESTART 128 
 int /*<<< orphan*/  B43_SHM_SCRATCH ; 
 int /*<<< orphan*/  b43_controller_restart (struct b43_wldev*,char*) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void b43_handle_firmware_panic(struct b43_wldev *dev)
{
	u16 reason;

	/* Read the register that contains the reason code for the panic. */
	reason = b43_shm_read16(dev, B43_SHM_SCRATCH, B43_FWPANIC_REASON_REG);
	b43err(dev->wl, "Whoopsy, firmware panic! Reason: %u\n", reason);

	switch (reason) {
	default:
		b43dbg(dev->wl, "The panic reason is unknown.\n");
		/* fallthrough */
	case B43_FWPANIC_DIE:
		/* Do not restart the controller or firmware.
		 * The device is nonfunctional from now on.
		 * Restarting would result in this panic to trigger again,
		 * so we avoid that recursion. */
		break;
	case B43_FWPANIC_RESTART:
		b43_controller_restart(dev, "Microcode panic");
		break;
	}
}