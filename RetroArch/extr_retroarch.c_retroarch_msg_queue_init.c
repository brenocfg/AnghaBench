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
 int /*<<< orphan*/  _runloop_msg_queue_lock ; 
 int /*<<< orphan*/  msg_queue_new (int) ; 
 int /*<<< orphan*/  retroarch_msg_queue_deinit () ; 
 int /*<<< orphan*/  runloop_msg_queue ; 
 int /*<<< orphan*/  slock_new () ; 

__attribute__((used)) static void retroarch_msg_queue_init(void)
{
   retroarch_msg_queue_deinit();
   runloop_msg_queue       = msg_queue_new(8);

#ifdef HAVE_THREADS
   _runloop_msg_queue_lock = slock_new();
#endif
}