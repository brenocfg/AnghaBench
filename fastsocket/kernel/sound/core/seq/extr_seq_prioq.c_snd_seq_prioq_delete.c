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
struct snd_seq_prioq {scalar_t__ cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_seq_prioq*) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  snd_seq_cell_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_prioq_cell_out (struct snd_seq_prioq*) ; 

void snd_seq_prioq_delete(struct snd_seq_prioq **fifo)
{
	struct snd_seq_prioq *f = *fifo;
	*fifo = NULL;

	if (f == NULL) {
		snd_printd("oops: snd_seq_prioq_delete() called with NULL prioq\n");
		return;
	}

	/* release resources...*/
	/*....................*/
	
	if (f->cells > 0) {
		/* drain prioQ */
		while (f->cells > 0)
			snd_seq_cell_free(snd_seq_prioq_cell_out(f));
	}
	
	kfree(f);
}