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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct w1_slave {TYPE_1__ dev; struct w1_f23_data* family_data; } ;
struct w1_f23_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct w1_f23_data*) ; 
 struct w1_f23_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_f23_bin_attr ; 

__attribute__((used)) static int w1_f23_add_slave(struct w1_slave *sl)
{
	int err;
#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	struct w1_f23_data *data;

	data = kzalloc(sizeof(struct w1_f23_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	sl->family_data = data;

#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */

	err = sysfs_create_bin_file(&sl->dev.kobj, &w1_f23_bin_attr);

#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	if (err)
		kfree(data);
#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */

	return err;
}