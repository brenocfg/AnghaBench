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
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loopback_queue ; 
 int /*<<< orphan*/  loopback_timer ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

void rose_loopback_init(void)
{
	skb_queue_head_init(&loopback_queue);

	init_timer(&loopback_timer);
}