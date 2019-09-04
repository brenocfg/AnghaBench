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
struct sched_param {int dummy; } ;
typedef  int /*<<< orphan*/  posix_spawnattr_t ;

/* Variables and functions */
 int ENOSYS ; 

int posix_spawnattr_setschedparam(posix_spawnattr_t *restrict attr,
	const struct sched_param *restrict schedparam)
{
	return ENOSYS;
}