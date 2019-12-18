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
struct TYPE_3__ {int freq0; int freq1; int tone_index; int gain1; int gain0; } ;
typedef  TYPE_1__ IXJ_TONE ;
typedef  int /*<<< orphan*/  IXJ ;

/* Variables and functions */
 scalar_t__ ixj_WriteDSPCommand (unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixj_init_tone(IXJ *j, IXJ_TONE * ti)
{
	int freq0, freq1;
	unsigned short data;
	if (ti->freq0) {
		freq0 = ti->freq0;
	} else {
		freq0 = 0x7FFF;
	}

	if (ti->freq1) {
		freq1 = ti->freq1;
	} else {
		freq1 = 0x7FFF;
	}

	if(ti->tone_index > 12 && ti->tone_index < 28)
	{
		if (ixj_WriteDSPCommand(0x6800 + ti->tone_index, j))
			return -1;
		if (ixj_WriteDSPCommand(0x6000 + (ti->gain1 << 4) + ti->gain0, j))
			return -1;
		data = freq0;
		if (ixj_WriteDSPCommand(data, j))
			return -1;
		data = freq1;
		if (ixj_WriteDSPCommand(data, j))
			return -1;
	}
	return freq0;
}