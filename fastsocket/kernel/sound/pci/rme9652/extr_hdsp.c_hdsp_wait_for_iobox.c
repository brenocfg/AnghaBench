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
struct hdsp {scalar_t__ io_type; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ H9632 ; 
 scalar_t__ H9652 ; 
 int HDSP_ConfigError ; 
 int /*<<< orphan*/  HDSP_FirmwareLoaded ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned int) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 

__attribute__((used)) static int hdsp_wait_for_iobox(struct hdsp *hdsp, unsigned int loops,
			       unsigned int delay)
{
	unsigned int i;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		return 0;

	for (i = 0; i != loops; ++i) {
		if (hdsp_read(hdsp, HDSP_statusRegister) & HDSP_ConfigError)
			msleep(delay);
		else {
			snd_printd("Hammerfall-DSP: iobox found after %ums!\n",
				   i * delay);
			return 0;
		}
	}

	snd_printk("Hammerfall-DSP: no Digiface or Multiface connected!\n");
	hdsp->state &= ~HDSP_FirmwareLoaded;
	return -EIO;
}