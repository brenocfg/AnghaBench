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
typedef  int u32 ;
struct maxiradio {int io; } ;

/* Variables and functions */
 int FREQ2BITS (int) ; 
 int /*<<< orphan*/  dprintk (struct maxiradio*,int,char*,int,int) ; 
 int /*<<< orphan*/  outbit (int,int) ; 
 int /*<<< orphan*/  turn_power (struct maxiradio*,int) ; 

__attribute__((used)) static void set_freq(struct maxiradio *dev, u32 freq)
{
	unsigned long int si;
	int bl;
	int io = dev->io;
	int val = FREQ2BITS(freq);

	/* TEA5757 shift register bits (see pdf) */

	outbit(0, io); /* 24  search */
	outbit(1, io); /* 23  search up/down */

	outbit(0, io); /* 22  stereo/mono */

	outbit(0, io); /* 21  band */
	outbit(0, io); /* 20  band (only 00=FM works I think) */

	outbit(0, io); /* 19  port ? */
	outbit(0, io); /* 18  port ? */

	outbit(0, io); /* 17  search level */
	outbit(0, io); /* 16  search level */

	si = 0x8000;
	for (bl = 1; bl <= 16; bl++) {
		outbit(val & si, io);
		si >>= 1;
	}

	dprintk(dev, 1, "Radio freq set to %d.%02d MHz\n",
				freq / 16000,
				freq % 16000 * 100 / 16000);

	turn_power(dev, 1);
}