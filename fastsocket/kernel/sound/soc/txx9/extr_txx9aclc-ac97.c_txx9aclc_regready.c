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
struct txx9aclc_soc_device {int dummy; } ;
struct txx9aclc_plat_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ACINTSTS ; 
 int ACINT_REGACCRDY ; 
 int __raw_readl (scalar_t__) ; 
 struct txx9aclc_plat_drvdata* txx9aclc_get_plat_drvdata (struct txx9aclc_soc_device*) ; 

__attribute__((used)) static int txx9aclc_regready(struct txx9aclc_soc_device *dev)
{
	struct txx9aclc_plat_drvdata *drvdata = txx9aclc_get_plat_drvdata(dev);

	return __raw_readl(drvdata->base + ACINTSTS) & ACINT_REGACCRDY;
}