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
typedef  int /*<<< orphan*/  u32 ;
struct ipw_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t store_mem_gpio_reg(struct device *d,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	u32 reg;
	struct ipw_priv *p = dev_get_drvdata(d);

	sscanf(buf, "%x", &reg);
	ipw_write_reg32(p, 0x301100, reg);
	return strnlen(buf, count);
}