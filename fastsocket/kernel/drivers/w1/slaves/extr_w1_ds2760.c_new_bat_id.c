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

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int /*<<< orphan*/  bat_idr ; 
 int /*<<< orphan*/  bat_idr_lock ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int new_bat_id(void)
{
	int ret;

	while (1) {
		int id;

		ret = idr_pre_get(&bat_idr, GFP_KERNEL);
		if (ret == 0)
			return -ENOMEM;

		mutex_lock(&bat_idr_lock);
		ret = idr_get_new(&bat_idr, NULL, &id);
		mutex_unlock(&bat_idr_lock);

		if (ret == 0) {
			ret = id & MAX_ID_MASK;
			break;
		} else if (ret == -EAGAIN) {
			continue;
		} else {
			break;
		}
	}

	return ret;
}