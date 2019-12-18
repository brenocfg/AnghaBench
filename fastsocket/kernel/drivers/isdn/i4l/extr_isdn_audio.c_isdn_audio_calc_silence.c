#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int idx; int state; } ;
typedef  TYPE_2__ silence_state ;
struct TYPE_5__ {int* vpar; } ;
struct TYPE_7__ {TYPE_1__ emu; TYPE_2__* silence_state; } ;
typedef  TYPE_3__ modem_info ;

/* Variables and functions */
 char abs (char) ; 
 char* isdn_audio_alaw_to_ulaw ; 

void
isdn_audio_calc_silence(modem_info * info, unsigned char *buf, int len, int fmt)
{
	silence_state *s = info->silence_state;
	int i;
	signed char c;

	if (!info->emu.vpar[1]) return;

	for (i = 0; i < len; i++) {
		if (fmt)
		    c = isdn_audio_alaw_to_ulaw[*buf++];
			else
		    c = *buf++;

		if (c > 0) c -= 128;
		c = abs(c);

		if (c > (info->emu.vpar[1] * 4)) { 
			s->idx = 0;
			s->state = 1; 
		} else {
			if (s->idx < 210000) s->idx++; 
		}
	}
}