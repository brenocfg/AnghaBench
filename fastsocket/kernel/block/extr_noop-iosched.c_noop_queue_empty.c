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
struct request_queue {TYPE_1__* elevator; } ;
struct noop_data {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {struct noop_data* elevator_data; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int noop_queue_empty(struct request_queue *q)
{
	struct noop_data *nd = q->elevator->elevator_data;

	return list_empty(&nd->queue);
}