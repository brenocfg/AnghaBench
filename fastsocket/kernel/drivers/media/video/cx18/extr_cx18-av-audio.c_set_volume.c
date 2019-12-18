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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 

__attribute__((used)) static void set_volume(struct cx18 *cx, int volume)
{
	/* First convert the volume to msp3400 values (0-127) */
	int vol = volume >> 9;
	/* now scale it up to cx18_av values
	 * -114dB to -96dB maps to 0
	 * this should be 19, but in my testing that was 4dB too loud */
	if (vol <= 23)
		vol = 0;
	else
		vol -= 23;

	/* PATH1_VOLUME */
	cx18_av_write(cx, 0x8d4, 228 - (vol * 2));
}