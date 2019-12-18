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
struct output_device {TYPE_1__* props; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int (* get_status ) (struct output_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (struct output_device*) ; 
 int stub2 (struct output_device*) ; 
 struct output_device* to_output_device (struct device*) ; 

__attribute__((used)) static ssize_t video_output_show_state(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	ssize_t ret_size = 0;
	struct output_device *od = to_output_device(dev);
	if (od->props)
		ret_size = sprintf(buf,"%.8x\n",od->props->get_status(od));
	return ret_size;
}