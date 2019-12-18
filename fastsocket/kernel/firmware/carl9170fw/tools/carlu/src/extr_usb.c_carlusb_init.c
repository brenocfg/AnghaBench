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
struct carlu {int* event_pipe; int /*<<< orphan*/  tx_queue_lock; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CreateMutex () ; 
 int /*<<< orphan*/  init_list_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carlusb_init(struct carlu *ar)
{
	init_list_head(&ar->tx_queue);
	ar->tx_queue_lock = SDL_CreateMutex();
	ar->event_pipe[0] = ar->event_pipe[1] = -1;

	return 0;
}