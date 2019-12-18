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
 size_t EV_SZ ; 
 size_t SEQ_MAX_QUEUE ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t qlen ; 
 size_t qtail ; 
 int /*<<< orphan*/ * queue ; 
 int /*<<< orphan*/  seq_playing ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  seq_startplay () ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seq_queue(unsigned char *note, char nonblock)
{

	/*
	 * Test if there is space in the queue
	 */

	if (qlen >= SEQ_MAX_QUEUE)
		if (!seq_playing)
			seq_startplay();	/*
						 * Give chance to drain the queue
						 */

	if (!nonblock && qlen >= SEQ_MAX_QUEUE && !waitqueue_active(&seq_sleeper)) {
		/*
		 * Sleep until there is enough space on the queue
		 */
		interruptible_sleep_on(&seq_sleeper);
	}
	if (qlen >= SEQ_MAX_QUEUE)
	{
		return 0;	/*
				 * To be sure
				 */
	}
	memcpy(&queue[qtail * EV_SZ], note, EV_SZ);

	qtail = (qtail + 1) % SEQ_MAX_QUEUE;
	qlen++;

	return 1;
}