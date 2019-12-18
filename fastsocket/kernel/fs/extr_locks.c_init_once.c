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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct file_lock *lock = (struct file_lock *) foo;

	locks_init_lock(lock);
}