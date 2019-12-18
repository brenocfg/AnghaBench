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
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;
struct sysfs_dirent {TYPE_1__ u; int /*<<< orphan*/  s_active; } ;

/* Variables and functions */
 int SD_DEACTIVATED_BIAS ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sysfs_put_active(struct sysfs_dirent *sd)
{
	int v;

	if (unlikely(!sd))
		return;

	v = atomic_dec_return(&sd->s_active);
	if (likely(v != SD_DEACTIVATED_BIAS))
		return;

	/* atomic_dec_return() is a mb(), we'll always see the updated
	 * sd->u.completion.
	 */
	complete(sd->u.completion);
}