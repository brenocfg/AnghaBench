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
struct thread_map {int nr; int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct thread_map* malloc (int) ; 

struct thread_map *thread_map__new_by_tid(pid_t tid)
{
	struct thread_map *threads = malloc(sizeof(*threads) + sizeof(pid_t));

	if (threads != NULL) {
		threads->map[0] = tid;
		threads->nr	= 1;
	}

	return threads;
}