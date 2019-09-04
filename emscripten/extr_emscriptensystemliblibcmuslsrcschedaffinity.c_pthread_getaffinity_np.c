#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int do_getaffinity (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

int pthread_getaffinity_np(pthread_t td, size_t size, cpu_set_t *set)
{
	return -do_getaffinity(td->tid, size, set);
}