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
struct i2c_adapter {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  i2c_adapter_idr ; 
 struct i2c_adapter* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct i2c_adapter* i2c_get_adapter(int id)
{
	struct i2c_adapter *adapter;

	mutex_lock(&core_lock);
	adapter = idr_find(&i2c_adapter_idr, id);
	if (adapter && !try_module_get(adapter->owner))
		adapter = NULL;

	mutex_unlock(&core_lock);
	return adapter;
}