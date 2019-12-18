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
struct drv_dev_and_id {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; TYPE_1__* drv; } ;
struct TYPE_2__ {long (* probe ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 long stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long local_pci_probe(void *_ddi)
{
	struct drv_dev_and_id *ddi = _ddi;

	return ddi->drv->probe(ddi->dev, ddi->id);
}