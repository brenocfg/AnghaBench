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
typedef  int /*<<< orphan*/  mp_sync_t ;
typedef  int /*<<< orphan*/  cpumask_t ;
typedef  int /*<<< orphan*/  cpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_cpus_call1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

cpu_t
mp_cpus_call(
	cpumask_t	cpus,
	mp_sync_t	mode,
        void		(*action_func)(void *),
        void		*arg)
{
	return mp_cpus_call1(
			cpus,
			mode,
			(void (*)(void *,void *))action_func,
			arg,
			NULL,
			NULL);
}