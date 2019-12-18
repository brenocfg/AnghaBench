#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned short* cram; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 scalar_t__ localPal ; 

__attribute__((used)) static int make_local_pal_sms(int fast_mode)
{
	unsigned short *spal = Pico.cram;
	unsigned int *dpal = (void *)localPal;
	unsigned int i, t;

	for (i = 0x40; i > 0; i--) {
		t = *spal++;
		t = ((t & 0x0003) << 22) | ((t & 0x000c) << 12) | ((t & 0x0030) << 2);
		t |= t >> 2;
		t |= t >> 4;
		*dpal++ = t;
	}

	return 0x40;
}