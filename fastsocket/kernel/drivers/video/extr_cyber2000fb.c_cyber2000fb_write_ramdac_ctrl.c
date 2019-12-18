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
struct cfb_info {unsigned int ramdac_ctrl; unsigned int ramdac_powerdown; } ;

/* Variables and functions */
 unsigned int cyber2000fb_readb (int,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_writeb (unsigned int,int,struct cfb_info*) ; 

__attribute__((used)) static void cyber2000fb_write_ramdac_ctrl(struct cfb_info *cfb)
{
	unsigned int i;
	unsigned int val = cfb->ramdac_ctrl | cfb->ramdac_powerdown;

	cyber2000fb_writeb(0x56, 0x3ce, cfb);
	i = cyber2000fb_readb(0x3cf, cfb);
	cyber2000fb_writeb(i | 4, 0x3cf, cfb);
	cyber2000fb_writeb(val, 0x3c6, cfb);
	cyber2000fb_writeb(i, 0x3cf, cfb);
}