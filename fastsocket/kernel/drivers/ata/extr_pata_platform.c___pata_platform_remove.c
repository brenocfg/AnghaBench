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
struct ata_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 struct ata_host* dev_get_drvdata (struct device*) ; 

int __pata_platform_remove(struct device *dev)
{
	struct ata_host *host = dev_get_drvdata(dev);

	ata_host_detach(host);

	return 0;
}