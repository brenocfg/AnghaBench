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
struct crypto4xx_device {int scatter_buffer_size; scalar_t__ scatter_buffer_pa; struct ce_sd* sdr; scalar_t__ sdr_pa; TYPE_1__* core_dev; void* scatter_buffer_va; } ;
struct ce_sd {scalar_t__ ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PPC4XX_NUM_SD ; 
 int PPC4XX_SD_BUFFER_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct ce_sd*,scalar_t__) ; 

__attribute__((used)) static u32 crypto4xx_build_sdr(struct crypto4xx_device *dev)
{
	int i;
	struct ce_sd *sd_array;

	/* alloc memory for scatter descriptor ring */
	dev->sdr = dma_alloc_coherent(dev->core_dev->device,
				      sizeof(struct ce_sd) * PPC4XX_NUM_SD,
				      &dev->sdr_pa, GFP_ATOMIC);
	if (!dev->sdr)
		return -ENOMEM;

	dev->scatter_buffer_size = PPC4XX_SD_BUFFER_SIZE;
	dev->scatter_buffer_va =
		dma_alloc_coherent(dev->core_dev->device,
			dev->scatter_buffer_size * PPC4XX_NUM_SD,
			&dev->scatter_buffer_pa, GFP_ATOMIC);
	if (!dev->scatter_buffer_va) {
		dma_free_coherent(dev->core_dev->device,
				  sizeof(struct ce_sd) * PPC4XX_NUM_SD,
				  dev->sdr, dev->sdr_pa);
		return -ENOMEM;
	}

	sd_array = dev->sdr;

	for (i = 0; i < PPC4XX_NUM_SD; i++) {
		sd_array[i].ptr = dev->scatter_buffer_pa +
				  dev->scatter_buffer_size * i;
	}

	return 0;
}