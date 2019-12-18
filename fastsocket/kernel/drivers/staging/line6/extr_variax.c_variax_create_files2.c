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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_active ; 
 int /*<<< orphan*/  dev_attr_bank ; 
 int /*<<< orphan*/  dev_attr_dump ; 
 int /*<<< orphan*/  dev_attr_model ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  dev_attr_raw ; 
 int /*<<< orphan*/  dev_attr_raw2 ; 
 int /*<<< orphan*/  dev_attr_tone ; 
 int /*<<< orphan*/  dev_attr_volume ; 
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int variax_create_files2(struct device *dev)
{
	int err;
	CHECK_RETURN(device_create_file(dev, &dev_attr_model));
	CHECK_RETURN(device_create_file(dev, &dev_attr_volume));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tone));
	CHECK_RETURN(device_create_file(dev, &dev_attr_name));
	CHECK_RETURN(device_create_file(dev, &dev_attr_bank));
	CHECK_RETURN(device_create_file(dev, &dev_attr_dump));
	CHECK_RETURN(device_create_file(dev, &dev_attr_active));
#if CREATE_RAW_FILE
	CHECK_RETURN(device_create_file(dev, &dev_attr_raw));
	CHECK_RETURN(device_create_file(dev, &dev_attr_raw2));
#endif
	return 0;
}