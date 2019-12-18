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
 int /*<<< orphan*/  print_opcode_name (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int scsi_command_size (unsigned char*) ; 

void __scsi_print_command(unsigned char *cdb)
{
	int k, len;

	print_opcode_name(cdb, 0);
	len = scsi_command_size(cdb);
	/* print out all bytes in cdb */
	for (k = 0; k < len; ++k) 
		printk(" %02x", cdb[k]);
	printk("\n");
}