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

/* Variables and functions */
 int CLOCK_TICK_RATE ; 
 int /*<<< orphan*/  pas_lock ; 
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 
 int pcm_channels ; 
 int pcm_filter ; 
 int pcm_speed ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcm_set_speed(int arg)
{
	int foo, tmp;
	unsigned long flags;

	if (arg == 0)
		return pcm_speed;

	if (arg > 44100)
		arg = 44100;
	if (arg < 5000)
		arg = 5000;

	if (pcm_channels & 2)
	{
		foo = ((CLOCK_TICK_RATE / 2) + (arg / 2)) / arg;
		arg = ((CLOCK_TICK_RATE / 2) + (foo / 2)) / foo;
	}
	else
	{
		foo = (CLOCK_TICK_RATE + (arg / 2)) / arg;
		arg = (CLOCK_TICK_RATE + (foo / 2)) / foo;
	}

	pcm_speed = arg;

	tmp = pas_read(0x0B8A);

	/*
	 * Set anti-aliasing filters according to sample rate. You really *NEED*
	 * to enable this feature for all normal recording unless you want to
	 * experiment with aliasing effects.
	 * These filters apply to the selected "recording" source.
	 * I (pfw) don't know the encoding of these 5 bits. The values shown
	 * come from the SDK found on ftp.uwp.edu:/pub/msdos/proaudio/.
	 *
	 * I cleared bit 5 of these values, since that bit controls the master
	 * mute flag. (Olav Wölfelschneider)
	 *
	 */
#if !defined NO_AUTO_FILTER_SET
	tmp &= 0xe0;
	if (pcm_speed >= 2 * 17897)
		tmp |= 0x01;
	else if (pcm_speed >= 2 * 15909)
		tmp |= 0x02;
	else if (pcm_speed >= 2 * 11931)
		tmp |= 0x09;
	else if (pcm_speed >= 2 * 8948)
		tmp |= 0x11;
	else if (pcm_speed >= 2 * 5965)
		tmp |= 0x19;
	else if (pcm_speed >= 2 * 2982)
		tmp |= 0x04;
	pcm_filter = tmp;
#endif

	spin_lock_irqsave(&pas_lock, flags);

	pas_write(tmp & ~(0x40 | 0x80), 0x0B8A);
	pas_write(0x00 | 0x30 | 0x04, 0x138B);
	pas_write(foo & 0xff, 0x1388);
	pas_write((foo >> 8) & 0xff, 0x1388);
	pas_write(tmp, 0x0B8A);

	spin_unlock_irqrestore(&pas_lock, flags);

	return pcm_speed;
}