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
struct iio_trigger {int id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_idr ; 
 int /*<<< orphan*/  iio_trigger_idr_lock ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iio_trigger_register_id(struct iio_trigger *trig_info)
{
	int ret = 0;

idr_again:
	if (unlikely(idr_pre_get(&iio_trigger_idr, GFP_KERNEL) == 0))
		return -ENOMEM;

	spin_lock(&iio_trigger_idr_lock);
	ret = idr_get_new(&iio_trigger_idr, NULL, &trig_info->id);
	spin_unlock(&iio_trigger_idr_lock);
	if (unlikely(ret == -EAGAIN))
		goto idr_again;
	else if (likely(!ret))
		trig_info->id = trig_info->id & MAX_ID_MASK;

	return ret;
}