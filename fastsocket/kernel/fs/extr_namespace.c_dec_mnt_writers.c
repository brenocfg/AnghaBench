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
struct vfsmount {int /*<<< orphan*/  mnt_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/ * per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline void dec_mnt_writers(struct vfsmount *mnt)
{
#ifdef CONFIG_SMP
	(*per_cpu_ptr(mnt->mnt_writers, smp_processor_id()))--;
#else
	mnt->mnt_writers--;
#endif
}