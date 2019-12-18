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
struct snd_seq_prioq {struct snd_seq_event_cell* head; } ;
struct snd_seq_event_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_printd (char*) ; 

struct snd_seq_event_cell *snd_seq_prioq_cell_peek(struct snd_seq_prioq * f)
{
	if (f == NULL) {
		snd_printd("oops: snd_seq_prioq_cell_in() called with NULL prioq\n");
		return NULL;
	}
	return f->head;
}