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
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 char* TPACPI_DESC ; 
 char* TPACPI_VERSION ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static ssize_t tpacpi_driver_version_show(struct device_driver *drv,
						char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s v%s\n",
			TPACPI_DESC, TPACPI_VERSION);
}