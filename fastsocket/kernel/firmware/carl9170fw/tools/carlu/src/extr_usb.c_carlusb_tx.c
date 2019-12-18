#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct frame {TYPE_1__ dcb; } ;
struct carlu {int /*<<< orphan*/  tx_queue_lock; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SDL_mutexP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_mutexV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carlusb_tx_pending (struct carlu*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void carlusb_tx(struct carlu *ar, struct frame *frame)
{
	BUG_ON(SDL_mutexP(ar->tx_queue_lock) != 0);

	list_add_tail(&frame->dcb.list, &ar->tx_queue);
	SDL_mutexV(ar->tx_queue_lock);

	carlusb_tx_pending(ar);
}