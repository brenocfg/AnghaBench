#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* dtmf_state; } ;
typedef  TYPE_1__ modem_info ;
struct TYPE_6__ {scalar_t__ idx; int* buf; } ;
typedef  TYPE_2__ dtmf_state ;

/* Variables and functions */
 int AMP_BITS ; 
 scalar_t__ DTMF_NPOINTS ; 
 int* isdn_audio_alaw_to_s16 ; 
 int /*<<< orphan*/  isdn_audio_goertzel (int*,TYPE_1__*) ; 
 int* isdn_audio_ulaw_to_s16 ; 

void
isdn_audio_calc_dtmf(modem_info * info, unsigned char *buf, int len, int fmt)
{
	dtmf_state *s = info->dtmf_state;
	int i;
	int c;

	while (len) {
		c = DTMF_NPOINTS - s->idx;
		if (c > len)
			c = len;
		if (c <= 0)
			break;
		for (i = 0; i < c; i++) {
			if (fmt)
				s->buf[s->idx++] =
				    isdn_audio_alaw_to_s16[*buf++] >> (15 - AMP_BITS);
			else
				s->buf[s->idx++] =
				    isdn_audio_ulaw_to_s16[*buf++] >> (15 - AMP_BITS);
		}
		if (s->idx == DTMF_NPOINTS) {
			isdn_audio_goertzel(s->buf, info);
			s->idx = 0;
		}
		len -= c;
	}
}