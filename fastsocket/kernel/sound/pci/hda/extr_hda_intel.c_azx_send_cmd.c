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
struct hda_bus {struct azx* private_data; } ;
struct azx {unsigned int* last_cmd; scalar_t__ single_cmd; scalar_t__ disabled; } ;

/* Variables and functions */
 size_t azx_command_addr (unsigned int) ; 
 int azx_corb_send_cmd (struct hda_bus*,unsigned int) ; 
 int azx_single_send_cmd (struct hda_bus*,unsigned int) ; 

__attribute__((used)) static int azx_send_cmd(struct hda_bus *bus, unsigned int val)
{
	struct azx *chip = bus->private_data;

	if (chip->disabled)
		return 0;
	chip->last_cmd[azx_command_addr(val)] = val;
	if (chip->single_cmd)
		return azx_single_send_cmd(bus, val);
	else
		return azx_corb_send_cmd(bus, val);
}