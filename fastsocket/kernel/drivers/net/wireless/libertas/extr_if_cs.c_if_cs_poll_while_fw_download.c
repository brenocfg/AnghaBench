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
typedef  scalar_t__ u8 ;
struct if_cs_card {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ if_cs_read8 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int if_cs_poll_while_fw_download(struct if_cs_card *card, uint addr, u8 reg)
{
	int i;

	for (i = 0; i < 100000; i++) {
		u8 val = if_cs_read8(card, addr);
		if (val == reg)
			return 0;
		udelay(5);
	}
	return -ETIME;
}