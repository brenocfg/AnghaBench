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
struct request_queue {struct elevator_queue* elevator; } ;
struct elevator_queue {void* elevator_data; } ;

/* Variables and functions */

__attribute__((used)) static void elevator_attach(struct request_queue *q, struct elevator_queue *eq,
			   void *data)
{
	q->elevator = eq;
	eq->elevator_data = data;
}