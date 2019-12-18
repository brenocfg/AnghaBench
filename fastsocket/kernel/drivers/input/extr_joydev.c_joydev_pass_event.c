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
struct js_event {int dummy; } ;
struct joydev_client {size_t head; scalar_t__ startup; int tail; int /*<<< orphan*/  fasync; int /*<<< orphan*/  buffer_lock; struct js_event* buffer; struct joydev* joydev; } ;
struct joydev {scalar_t__ nabs; scalar_t__ nkey; } ;

/* Variables and functions */
 int JOYDEV_BUFFER_SIZE ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void joydev_pass_event(struct joydev_client *client,
			      struct js_event *event)
{
	struct joydev *joydev = client->joydev;

	/*
	 * IRQs already disabled, just acquire the lock
	 */
	spin_lock(&client->buffer_lock);

	client->buffer[client->head] = *event;

	if (client->startup == joydev->nabs + joydev->nkey) {
		client->head++;
		client->head &= JOYDEV_BUFFER_SIZE - 1;
		if (client->tail == client->head)
			client->startup = 0;
	}

	spin_unlock(&client->buffer_lock);

	kill_fasync(&client->fasync, SIGIO, POLL_IN);
}