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
typedef  int /*<<< orphan*/  main_async_t ;

/* Variables and functions */
 int /*<<< orphan*/ * async_queue ; 
 int /*<<< orphan*/  async_queue_semaphore ; 
 int /*<<< orphan*/  dispatch_semaphore_create (int) ; 
 int /*<<< orphan*/  ev_async_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_async ; 
 int /*<<< orphan*/  main_async_drain ; 
 scalar_t__ malloc (int) ; 
 int queue_length ; 

void main_async_init(void)
{
	async_queue_semaphore = dispatch_semaphore_create(1);
	async_queue = (main_async_t*)malloc(sizeof(main_async_t) * queue_length);
	ev_async_init(&main_async, main_async_drain);
}