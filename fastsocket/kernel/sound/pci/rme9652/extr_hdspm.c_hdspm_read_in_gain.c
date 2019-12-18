#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hdspm {TYPE_2__* mixer; } ;
struct TYPE_4__ {TYPE_1__* ch; } ;
struct TYPE_3__ {int* in; } ;

/* Variables and functions */
 unsigned int HDSPM_MIXER_CHANNELS ; 

__attribute__((used)) static inline int hdspm_read_in_gain(struct hdspm * hdspm, unsigned int chan,
				     unsigned int in)
{
	if (chan >= HDSPM_MIXER_CHANNELS || in >= HDSPM_MIXER_CHANNELS)
		return 0;

	return hdspm->mixer->ch[chan].in[in];
}