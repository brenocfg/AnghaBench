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
 int /*<<< orphan*/  MX21ADS_IO_REG ; 
 int MX21ADS_IO_SD_WP ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx21ads_sdhc_get_ro(struct device *dev)
{
	return (__raw_readw(MX21ADS_IO_REG) & MX21ADS_IO_SD_WP) ? 1 : 0;
}