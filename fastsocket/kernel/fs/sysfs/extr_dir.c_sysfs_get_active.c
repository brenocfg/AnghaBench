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
struct sysfs_dirent {int /*<<< orphan*/  s_active; } ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sysfs_dirent *sysfs_get_active(struct sysfs_dirent *sd)
{
	if (unlikely(!sd))
		return NULL;

	while (1) {
		int v, t;

		v = atomic_read(&sd->s_active);
		if (unlikely(v < 0))
			return NULL;

		t = atomic_cmpxchg(&sd->s_active, v, v + 1);
		if (likely(t == v))
			return sd;
		if (t < 0)
			return NULL;

		cpu_relax();
	}
}