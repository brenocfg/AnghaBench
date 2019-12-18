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
struct snd_seq_fifo {scalar_t__ pool; int /*<<< orphan*/  input_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_seq_fifo*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_fifo_clear (struct snd_seq_fifo*) ; 
 int /*<<< orphan*/  snd_seq_pool_delete (scalar_t__*) ; 
 int /*<<< orphan*/  snd_seq_pool_done (scalar_t__) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_seq_fifo_delete(struct snd_seq_fifo **fifo)
{
	struct snd_seq_fifo *f;

	if (snd_BUG_ON(!fifo))
		return;
	f = *fifo;
	if (snd_BUG_ON(!f))
		return;
	*fifo = NULL;

	snd_seq_fifo_clear(f);

	/* wake up clients if any */
	if (waitqueue_active(&f->input_sleep))
		wake_up(&f->input_sleep);

	/* release resources...*/
	/*....................*/

	if (f->pool) {
		snd_seq_pool_done(f->pool);
		snd_seq_pool_delete(&f->pool);
	}
	
	kfree(f);
}