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
struct sym53c500_data {int fast_pio; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
SYM53C500_store_pio(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t count)
{
	int pio;
	struct Scsi_Host *SHp = class_to_shost(dev);
	struct sym53c500_data *data =
	    (struct sym53c500_data *)SHp->hostdata;

	pio = simple_strtoul(buf, NULL, 0);
	if (pio == 0 || pio == 1) {
		data->fast_pio = pio;
		return count;
	}
	else
		return -EINVAL;
}