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
struct env {scalar_t__ regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ REG_STAT ; 
 struct env* dev_get_drvdata (struct device*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_fwver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct env *p = dev_get_drvdata(dev);
	u8 val;

	val = readb(p->regs + REG_STAT);
	return sprintf(buf, "%d\n", val >> 4);
}