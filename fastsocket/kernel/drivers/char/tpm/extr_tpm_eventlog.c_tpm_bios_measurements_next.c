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
struct tpm_bios_log {void* bios_event_log_end; } ;
struct tcpa_event {scalar_t__ event_size; scalar_t__ event_type; } ;
struct seq_file {struct tpm_bios_log* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */

__attribute__((used)) static void *tpm_bios_measurements_next(struct seq_file *m, void *v,
					loff_t *pos)
{
	struct tcpa_event *event = v;
	struct tpm_bios_log *log = m->private;
	void *limit = log->bios_event_log_end;

	v += sizeof(struct tcpa_event) + event->event_size;

	/* now check if current entry is valid */
	if ((v + sizeof(struct tcpa_event)) >= limit)
		return NULL;

	event = v;

	if (event->event_type == 0 && event->event_size == 0)
		return NULL;

	if ((event->event_type == 0 && event->event_size == 0) ||
	    ((v + sizeof(struct tcpa_event) + event->event_size) >= limit))
		return NULL;

	(*pos)++;
	return v;
}