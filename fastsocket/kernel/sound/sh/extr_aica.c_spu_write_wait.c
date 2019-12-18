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
 int /*<<< orphan*/  G2_FIFO ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 

__attribute__((used)) static void spu_write_wait(void)
{
	int time_count;
	time_count = 0;
	while (1) {
		if (!(readl(G2_FIFO) & 0x11))
			break;
		/* To ensure hardware failure doesn't wedge kernel */
		time_count++;
		if (time_count > 0x10000) {
			snd_printk
			    ("WARNING: G2 FIFO appears to be blocked.\n");
			break;
		}
	}
}