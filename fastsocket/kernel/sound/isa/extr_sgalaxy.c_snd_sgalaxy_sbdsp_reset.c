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
 int /*<<< orphan*/  DATA_AVAIL ; 
 int ENODEV ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SBP1 (unsigned long,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_sgalaxy_sbdsp_reset(unsigned long port)
{
	int i;

	outb(1, SBP1(port, RESET));
	udelay(10);
	outb(0, SBP1(port, RESET));
	udelay(30);
	for (i = 0; i < 1000 && !(inb(SBP1(port, DATA_AVAIL)) & 0x80); i++);
	if (inb(SBP1(port, READ)) != 0xaa) {
		snd_printd("sb_reset: failed at 0x%lx!!!\n", port);
		return -ENODEV;
	}
	return 0;
}