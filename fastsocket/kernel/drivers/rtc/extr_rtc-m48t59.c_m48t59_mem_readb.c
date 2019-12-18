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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct platform_device {int dummy; } ;
struct m48t59_private {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct m48t59_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static u8
m48t59_mem_readb(struct device *dev, u32 ofs)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);

	return readb(m48t59->ioaddr+ofs);
}