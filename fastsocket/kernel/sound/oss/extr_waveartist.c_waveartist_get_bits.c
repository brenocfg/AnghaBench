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
struct TYPE_3__ {scalar_t__ audio_format; } ;
typedef  TYPE_1__ wavnc_port_info ;

/* Variables and functions */
 scalar_t__ AFMT_S16_LE ; 
 scalar_t__ AFMT_S8 ; 

__attribute__((used)) static unsigned int
waveartist_get_bits(wavnc_port_info *portc)
{
	unsigned int bits;

	if (portc->audio_format == AFMT_S16_LE)
		bits = 1;
	else if (portc->audio_format == AFMT_S8)
		bits = 0;
	else
		bits = 2;	//default AFMT_U8

	return bits;
}