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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPAL_EC_COMMAND_WIRELESS ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_raw(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	u8 result;

	ec_read(COMPAL_EC_COMMAND_WIRELESS, &result);

	return sprintf(buf, "%i\n", result);
}