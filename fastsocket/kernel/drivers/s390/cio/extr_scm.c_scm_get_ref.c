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
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* eadm_ops ; 
 int /*<<< orphan*/  eadm_ops_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int scm_get_ref(void)
{
	int ret = 0;

	mutex_lock(&eadm_ops_mutex);
	if (!eadm_ops || !try_module_get(eadm_ops->owner))
		ret = -ENOENT;
	mutex_unlock(&eadm_ops_mutex);

	return ret;
}