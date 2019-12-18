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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_IFORM ; 
 int /*<<< orphan*/  LM1882_SYNC_DRIVE ; 
 int /*<<< orphan*/  btaor (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 

__attribute__((used)) static void init_ids_eagle(struct bttv *btv)
{
	gpio_inout(0xffffff,0xFFFF37);
	gpio_write(0x200020);

	/* flash strobe inverter ?! */
	gpio_write(0x200024);

	/* switch sync drive off */
	gpio_bits(LM1882_SYNC_DRIVE,LM1882_SYNC_DRIVE);

	/* set BT848 muxel to 2 */
	btaor((2)<<5, ~(2<<5), BT848_IFORM);
}