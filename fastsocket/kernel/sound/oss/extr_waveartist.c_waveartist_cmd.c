#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int io_base; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ wavnc_info ;

/* Variables and functions */
 scalar_t__ CMDR ; 
 int CMD_RF ; 
 int CMD_WE ; 
 int DEBUG_CMD ; 
 scalar_t__ STATR ; 
 int debug_flg ; 
 int inb (scalar_t__) ; 
 void* inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
waveartist_cmd(wavnc_info *devc,
		int nr_cmd, unsigned int *cmd,
		int nr_resp, unsigned int *resp)
{
	unsigned int io_base = devc->hw.io_base;
	unsigned int timed_out = 0;
	unsigned int i;

	if (debug_flg & DEBUG_CMD) {
		printk("waveartist_cmd: cmd=");

		for (i = 0; i < nr_cmd; i++)
			printk("%04X ", cmd[i]);

		printk("\n");
	}

	if (inb(io_base + STATR) & CMD_RF) {
		int old_data;

		/* flush the port
		 */

		old_data = inw(io_base + CMDR);

		if (debug_flg & DEBUG_CMD)
			printk("flushed %04X...", old_data);

		udelay(10);
	}

	for (i = 0; !timed_out && i < nr_cmd; i++) {
		int count;

		for (count = 5000; count; count--)
			if (inb(io_base + STATR) & CMD_WE)
				break;

		if (!count)
			timed_out = 1;
		else
			outw(cmd[i], io_base + CMDR);
	}

	for (i = 0; !timed_out && i < nr_resp; i++) {
		int count;

		for (count = 5000; count; count--)
			if (inb(io_base + STATR) & CMD_RF)
				break;

		if (!count)
			timed_out = 1;
		else
			resp[i] = inw(io_base + CMDR);
	}

	if (debug_flg & DEBUG_CMD) {
		if (!timed_out) {
			printk("waveartist_cmd: resp=");

			for (i = 0; i < nr_resp; i++)
				printk("%04X ", resp[i]);

			printk("\n");
		} else
			printk("waveartist_cmd: timed out\n");
	}

	return timed_out ? 1 : 0;
}