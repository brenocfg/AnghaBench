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
struct i2c_adapter {int nr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  i2c_adapter_idr ; 
 int i2c_register_adapter (struct i2c_adapter*) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct i2c_adapter*,int,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i2c_add_numbered_adapter(struct i2c_adapter *adap)
{
	int	id;
	int	status;

	if (adap->nr & ~MAX_ID_MASK)
		return -EINVAL;

retry:
	if (idr_pre_get(&i2c_adapter_idr, GFP_KERNEL) == 0)
		return -ENOMEM;

	mutex_lock(&core_lock);
	/* "above" here means "above or equal to", sigh;
	 * we need the "equal to" result to force the result
	 */
	status = idr_get_new_above(&i2c_adapter_idr, adap, adap->nr, &id);
	if (status == 0 && id != adap->nr) {
		status = -EBUSY;
		idr_remove(&i2c_adapter_idr, id);
	}
	mutex_unlock(&core_lock);
	if (status == -EAGAIN)
		goto retry;

	if (status == 0)
		status = i2c_register_adapter(adap);
	return status;
}