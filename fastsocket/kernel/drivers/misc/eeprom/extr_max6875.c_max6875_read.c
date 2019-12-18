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
struct max6875_data {int /*<<< orphan*/ * data; } ;
struct kobject {int dummy; } ;
struct i2c_client {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t SLICE_BITS ; 
 size_t USER_EEPROM_SIZE ; 
 struct max6875_data* i2c_get_clientdata (struct i2c_client*) ; 
 struct i2c_client* kobj_to_i2c_client (struct kobject*) ; 
 int /*<<< orphan*/  max6875_update_slice (struct i2c_client*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t max6875_read(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr,
			    char *buf, loff_t off, size_t count)
{
	struct i2c_client *client = kobj_to_i2c_client(kobj);
	struct max6875_data *data = i2c_get_clientdata(client);
	int slice, max_slice;

	if (off > USER_EEPROM_SIZE)
		return 0;

	if (off + count > USER_EEPROM_SIZE)
		count = USER_EEPROM_SIZE - off;

	/* refresh slices which contain requested bytes */
	max_slice = (off + count - 1) >> SLICE_BITS;
	for (slice = (off >> SLICE_BITS); slice <= max_slice; slice++)
		max6875_update_slice(client, slice);

	memcpy(buf, &data->data[off], count);

	return count;
}