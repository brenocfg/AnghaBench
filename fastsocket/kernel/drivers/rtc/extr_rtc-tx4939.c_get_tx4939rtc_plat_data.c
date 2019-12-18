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
struct tx4939rtc_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tx4939rtc_plat_data* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static struct tx4939rtc_plat_data *get_tx4939rtc_plat_data(struct device *dev)
{
	return platform_get_drvdata(to_platform_device(dev));
}