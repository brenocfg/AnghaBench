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
struct TYPE_2__ {int /*<<< orphan*/  (* send_sysex ) (unsigned int,unsigned char*,int) ;} ;

/* Variables and functions */
 unsigned int max_synthdev ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned char*,int) ; 
 TYPE_1__** synth_devs ; 
 int synth_open_mask ; 

__attribute__((used)) static void seq_sysex_message(unsigned char *event_rec)
{
	unsigned int dev = event_rec[1];
	int i, l = 0;
	unsigned char  *buf = &event_rec[2];

	if (dev > max_synthdev)
		return;
	if (!(synth_open_mask & (1 << dev)))
		return;
	if (!synth_devs[dev])
		return;

	l = 0;
	for (i = 0; i < 6 && buf[i] != 0xff; i++)
		l = i + 1;

	if (!synth_devs[dev]->send_sysex)
		return;
	if (l > 0)
		synth_devs[dev]->send_sysex(dev, buf, l);
}