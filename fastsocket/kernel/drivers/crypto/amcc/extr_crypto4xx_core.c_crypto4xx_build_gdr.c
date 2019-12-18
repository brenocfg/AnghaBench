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
typedef  int /*<<< orphan*/  u32 ;
struct crypto4xx_device {int /*<<< orphan*/  gdr; int /*<<< orphan*/  gdr_pa; TYPE_1__* core_dev; } ;
struct ce_gd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PPC4XX_NUM_GD ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 crypto4xx_build_gdr(struct crypto4xx_device *dev)
{
	dev->gdr = dma_alloc_coherent(dev->core_dev->device,
				      sizeof(struct ce_gd) * PPC4XX_NUM_GD,
				      &dev->gdr_pa, GFP_ATOMIC);
	if (!dev->gdr)
		return -ENOMEM;

	memset(dev->gdr, 0, sizeof(struct ce_gd) * PPC4XX_NUM_GD);

	return 0;
}