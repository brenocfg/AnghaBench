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

/* Variables and functions */
 int /*<<< orphan*/  GPIO2_OUTPUT ; 
 int /*<<< orphan*/  GPIO2_PINSTATE ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xxs1500_pcmcia_shutdown(void)
{
	/* turn off power */
	au_writel(au_readl(GPIO2_PINSTATE) | (1<<14)|(1<<30),
			GPIO2_OUTPUT);
	au_sync_delay(100);

	/* assert reset */
	au_writel(au_readl(GPIO2_PINSTATE) | (1<<4)|(1<<20),
			GPIO2_OUTPUT);
	au_sync_delay(100);
	return 0;
}