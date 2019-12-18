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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X1205_ALM0_BASE ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 int x1205_set_datetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x1205_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	return x1205_set_datetime(to_i2c_client(dev),
		&alrm->time, 1, X1205_ALM0_BASE, alrm->enabled);
}