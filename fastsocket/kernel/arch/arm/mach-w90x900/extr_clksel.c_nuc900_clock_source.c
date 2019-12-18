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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int EXT ; 
 unsigned int OTHER ; 
 unsigned int PLL0 ; 
 unsigned int PLL1 ; 
 int /*<<< orphan*/  clksel_sem ; 
 int /*<<< orphan*/  clock_source_select (char const*,unsigned int) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (unsigned char*,char*) ; 

void nuc900_clock_source(struct device *dev, unsigned char *src)
{
	unsigned int clkval;
	const char *dev_id;

	BUG_ON(!src);
	clkval = 0;

	mutex_lock(&clksel_sem);

	if (dev)
		dev_id = dev_name(dev);
	else
		dev_id = "cpufreq";

	if (strcmp(src, "pll0") == 0)
		clkval = PLL0;
	else if (strcmp(src, "pll1") == 0)
		clkval = PLL1;
	else if (strcmp(src, "ext") == 0)
		clkval = EXT;
	else if (strcmp(src, "oth") == 0)
		clkval = OTHER;

	clock_source_select(dev_id, clkval);

	mutex_unlock(&clksel_sem);
}