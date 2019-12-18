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
typedef  int u32 ;
struct crypto4xx_device {struct ce_pd* pdr; scalar_t__ pdr_pa; } ;
struct ce_pd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static struct ce_pd *crypto4xx_get_pdp(struct crypto4xx_device *dev,
				       dma_addr_t *pd_dma, u32 idx)
{
	*pd_dma = dev->pdr_pa + sizeof(struct ce_pd) * idx;

	return dev->pdr + sizeof(struct ce_pd) * idx;
}