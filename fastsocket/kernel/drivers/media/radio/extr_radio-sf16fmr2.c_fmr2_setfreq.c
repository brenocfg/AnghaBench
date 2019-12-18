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
struct fmr2 {unsigned long curfreq; int /*<<< orphan*/  io; int /*<<< orphan*/  stereo; } ;

/* Variables and functions */
 int RSF16_ENCODE (unsigned long) ; 
 int /*<<< orphan*/  fmr2_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmr2_stereo_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmr2_unmute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outbits (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fmr2_setfreq(struct fmr2 *dev)
{
	unsigned long freq = dev->curfreq;

	fmr2_mute(dev->io);

	/* 0x42 for mono output
	 * 0x102 forward scanning
	 * 0x182 scansione avanti
	 */
	outbits(9, 0x2, 3, dev->io);
	outbits(16, RSF16_ENCODE(freq), 2, dev->io);

	fmr2_unmute(dev->io);

	/* wait 0.11 sec */
	msleep(110);

	/* NOTE if mute this stop radio
	   you must set freq on unmute */
	dev->stereo = fmr2_stereo_mode(dev->io);
	return 0;
}