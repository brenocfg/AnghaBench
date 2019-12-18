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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAPS_PORT_TEMP2 ; 
 int hdaps_readb_one (int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t hdaps_temp2_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	u8 temp;
	int ret;

	ret = hdaps_readb_one(HDAPS_PORT_TEMP2, &temp);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%u\n", temp);
}