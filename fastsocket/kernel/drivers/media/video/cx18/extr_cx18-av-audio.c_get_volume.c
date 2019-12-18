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
 int cx18_av_read (struct cx18*,int) ; 

__attribute__((used)) static int get_volume(struct cx18 *cx)
{
	/* Volume runs +18dB to -96dB in 1/2dB steps
	 * change to fit the msp3400 -114dB to +12dB range */

	/* check PATH1_VOLUME */
	int vol = 228 - cx18_av_read(cx, 0x8d4);
	vol = (vol / 2) + 23;
	return vol << 9;
}