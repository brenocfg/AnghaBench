#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (TYPE_1__*) ;} ;
struct nomadik_nand_host {TYPE_1__ mtd; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct nomadik_nand_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int nomadik_nand_resume(struct device *dev)
{
	struct nomadik_nand_host *host = dev_get_drvdata(dev);
	if (host)
		host->mtd.resume(&host->mtd);
	return 0;
}