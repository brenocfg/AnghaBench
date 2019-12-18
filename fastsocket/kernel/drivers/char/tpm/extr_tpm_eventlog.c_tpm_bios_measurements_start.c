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
struct tpm_bios_log {void* bios_event_log_end; void* bios_event_log; } ;
struct tcpa_event {scalar_t__ event_type; scalar_t__ event_size; } ;
struct seq_file {struct tpm_bios_log* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static void *tpm_bios_measurements_start(struct seq_file *m, loff_t *pos)
{
	loff_t i;
	struct tpm_bios_log *log = m->private;
	void *addr = log->bios_event_log;
	void *limit = log->bios_event_log_end;
	struct tcpa_event *event;

	/* read over *pos measurements */
	for (i = 0; i < *pos; i++) {
		event = addr;

		if ((addr + sizeof(struct tcpa_event)) < limit) {
			if (event->event_type == 0 && event->event_size == 0)
				return NULL;
			addr += sizeof(struct tcpa_event) + event->event_size;
		}
	}

	/* now check if current entry is valid */
	if ((addr + sizeof(struct tcpa_event)) >= limit)
		return NULL;

	event = addr;

	if ((event->event_type == 0 && event->event_size == 0) ||
	    ((addr + sizeof(struct tcpa_event) + event->event_size) >= limit))
		return NULL;

	return addr;
}