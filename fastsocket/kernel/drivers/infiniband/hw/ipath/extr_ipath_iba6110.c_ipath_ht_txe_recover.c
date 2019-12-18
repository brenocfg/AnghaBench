#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipath_devdata {TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sps_txeparity; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ ipath_stats ; 

__attribute__((used)) static void ipath_ht_txe_recover(struct ipath_devdata *dd)
{
	++ipath_stats.sps_txeparity;
	dev_info(&dd->pcidev->dev,
		"Recovering from TXE PIO parity error\n");
}