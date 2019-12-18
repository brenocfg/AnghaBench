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
typedef  int ino_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_get_new_above (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_ino_ida ; 
 int /*<<< orphan*/  sysfs_ino_lock ; 

__attribute__((used)) static int sysfs_alloc_ino(ino_t *pino)
{
	int ino, rc;

 retry:
	spin_lock(&sysfs_ino_lock);
	rc = ida_get_new_above(&sysfs_ino_ida, 2, &ino);
	spin_unlock(&sysfs_ino_lock);

	if (rc == -EAGAIN) {
		if (ida_pre_get(&sysfs_ino_ida, GFP_KERNEL))
			goto retry;
		rc = -ENOMEM;
	}

	*pino = ino;
	return rc;
}