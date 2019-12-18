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
struct hdsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_fifoStatus ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printk (char*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hdsp_fifo_wait(struct hdsp *hdsp, int count, int timeout)
{
	int i;

	/* the fifoStatus registers reports on how many words
	   are available in the command FIFO.
	*/

	for (i = 0; i < timeout; i++) {

		if ((int)(hdsp_read (hdsp, HDSP_fifoStatus) & 0xff) <= count)
			return 0;

		/* not very friendly, but we only do this during a firmware
		   load and changing the mixer, so we just put up with it.
		*/

		udelay (100);
	}

	snd_printk ("Hammerfall-DSP: wait for FIFO status <= %d failed after %d iterations\n",
		    count, timeout);
	return -1;
}