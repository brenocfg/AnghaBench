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
typedef  int /*<<< orphan*/  __gthread_recursive_mutex_t ;

/* Variables and functions */
 int __gthread_mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *mutex)
{
  return __gthread_mutex_trylock (mutex);
}