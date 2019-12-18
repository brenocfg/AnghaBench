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
struct tcpa_event {int event_size; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int tpm_binary_bios_measurements_show(struct seq_file *m, void *v)
{
	struct tcpa_event *event = v;
	char *data = v;
	int i;

	for (i = 0; i < sizeof(struct tcpa_event) + event->event_size; i++)
		seq_putc(m, data[i]);

	return 0;
}