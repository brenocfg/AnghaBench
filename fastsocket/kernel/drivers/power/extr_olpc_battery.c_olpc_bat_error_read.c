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
typedef  int uint8_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EC_BAT_ERRCODE ; 
 scalar_t__ olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t olpc_bat_error_read(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	uint8_t ec_byte;
	ssize_t ret;

	ret = olpc_ec_cmd(EC_BAT_ERRCODE, NULL, 0, &ec_byte, 1);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", ec_byte);
}