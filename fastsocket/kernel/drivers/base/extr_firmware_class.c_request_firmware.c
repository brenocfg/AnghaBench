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
struct firmware {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int _request_firmware (struct firmware const**,char const*,struct device*,int) ; 

int
request_firmware(const struct firmware **firmware_p, const char *name,
                 struct device *device)
{
        int uevent = 1;
        return _request_firmware(firmware_p, name, device, uevent);
}