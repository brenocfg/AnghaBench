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
 int /*<<< orphan*/  mbuf_worker_ready ; 
 int /*<<< orphan*/  mbuf_worker_thread () ; 

__attribute__((used)) __attribute__((noreturn))
static void
mbuf_worker_thread_init(void)
{
	mbuf_worker_ready++;
	mbuf_worker_thread();
}