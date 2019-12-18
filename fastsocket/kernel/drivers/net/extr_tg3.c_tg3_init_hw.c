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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3PCI_MEM_WIN_BASE_ADDR ; 
 int /*<<< orphan*/  tg3_enable_register_access (struct tg3*) ; 
 int /*<<< orphan*/  tg3_poll_fw (struct tg3*) ; 
 int tg3_reset_hw (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_switch_clocks (struct tg3*) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_init_hw(struct tg3 *tp, bool reset_phy)
{
	/* Chip may have been just powered on. If so, the boot code may still
	 * be running initialization. Wait for it to finish to avoid races in
	 * accessing the hardware.
	 */
	tg3_enable_register_access(tp);
	tg3_poll_fw(tp);

	tg3_switch_clocks(tp);

	tw32(TG3PCI_MEM_WIN_BASE_ADDR, 0);

	return tg3_reset_hw(tp, reset_phy);
}