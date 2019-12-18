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
typedef  char* u32 ;
struct seq_file {struct acpi_ec* private; } ;
struct acpi_ec {scalar_t__ global_lock; scalar_t__ data_addr; scalar_t__ command_addr; scalar_t__ gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int acpi_ec_read_info(struct seq_file *seq, void *offset)
{
	struct acpi_ec *ec = seq->private;

	if (!ec)
		goto end;

	seq_printf(seq, "gpe:\t\t\t0x%02x\n", (u32) ec->gpe);
	seq_printf(seq, "ports:\t\t\t0x%02x, 0x%02x\n",
		   (unsigned)ec->command_addr, (unsigned)ec->data_addr);
	seq_printf(seq, "use global lock:\t%s\n",
		   ec->global_lock ? "yes" : "no");
      end:
	return 0;
}