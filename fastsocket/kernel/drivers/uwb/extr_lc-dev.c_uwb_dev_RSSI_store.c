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
struct uwb_dev {struct uwb_beca_e* bce; } ;
struct uwb_beca_e {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rssi_stats; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_store (int /*<<< orphan*/ *,char const*,size_t) ; 
 struct uwb_dev* to_uwb_dev (struct device*) ; 

__attribute__((used)) static ssize_t uwb_dev_RSSI_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);
	struct uwb_beca_e *bce = uwb_dev->bce;
	ssize_t result;

	mutex_lock(&bce->mutex);
	result = stats_store(&uwb_dev->bce->rssi_stats, buf, size);
	mutex_unlock(&bce->mutex);
	return result;
}