#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* completion; } ;
struct sysfs_dirent {int s_flags; int /*<<< orphan*/  s_active; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int SD_DEACTIVATED_BIAS ; 
 int SYSFS_FLAG_REMOVED ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sysfs_deactivate(struct sysfs_dirent *sd)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	int v;

	BUG_ON(!(sd->s_flags & SYSFS_FLAG_REMOVED));
	sd->u.completion = (void *)&wait;

	/* atomic_add_return() is a mb(), put_active() will always see
	 * the updated sd->u.completion.
	 */
	v = atomic_add_return(SD_DEACTIVATED_BIAS, &sd->s_active);

	if (v != SD_DEACTIVATED_BIAS)
		wait_for_completion(&wait);
}