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
struct carlu {int /*<<< orphan*/ * tx_sent_queue; int /*<<< orphan*/  resp_pend; int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  resp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 unsigned int __AR9170_NUM_TXQ ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  frame_queue_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct carlu*) ; 

void carlu_free_driver(struct carlu *ar)
{
	unsigned int i;

	dbg("destroy driver struct.\n");
	SDL_DestroyMutex(ar->resp_lock);
	SDL_DestroyMutex(ar->mem_lock);
	SDL_DestroyCond(ar->resp_pend);

	for (i = 0; i < __AR9170_NUM_TXQ; i++)
		frame_queue_kill(&ar->tx_sent_queue[i]);

	free(ar);
}