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
typedef  int /*<<< orphan*/  sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  DSP_READ ; 
 int inb (int /*<<< orphan*/ ) ; 

int sb_dsp_get_byte(sb_devc * devc)
{
	int i;

	for (i = 1000; i; i--)
	{
		if (inb(DSP_DATA_AVAIL) & 0x80)
			return inb(DSP_READ);
	}
	return 0xffff;
}