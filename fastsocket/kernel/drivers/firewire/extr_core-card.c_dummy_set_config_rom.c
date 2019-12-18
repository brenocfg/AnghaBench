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
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static int dummy_set_config_rom(struct fw_card *card,
				u32 *config_rom, size_t length)
{
	/*
	 * We take the card out of card_list before setting the dummy
	 * driver, so this should never get called.
	 */
	BUG();
	return -1;
}