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
struct ipw2100_priv {int status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int STATUS_RF_KILL_SW ; 
 struct ipw2100_priv* dev_get_drvdata (struct device*) ; 
 scalar_t__ rf_kill_active (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_rf_kill(struct device *d, struct device_attribute *attr,
			    char *buf)
{
	/* 0 - RF kill not enabled
	   1 - SW based RF kill active (sysfs)
	   2 - HW based RF kill active
	   3 - Both HW and SW baed RF kill active */
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	int val = ((priv->status & STATUS_RF_KILL_SW) ? 0x1 : 0x0) |
	    (rf_kill_active(priv) ? 0x2 : 0x0);
	return sprintf(buf, "%i\n", val);
}