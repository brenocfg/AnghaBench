#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ plx; } ;
typedef  TYPE_1__ card_t ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PLX_MAILBOX_1 ; 
 int jiffies ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wanxl_puts_command(card_t *card, u32 cmd)
{
	unsigned long timeout = jiffies + 5 * HZ;

	writel(cmd, card->plx + PLX_MAILBOX_1);
	do {
		if (readl(card->plx + PLX_MAILBOX_1) == 0)
			return 0;

		schedule();
	}while (time_after(timeout, jiffies));

	return -1;
}