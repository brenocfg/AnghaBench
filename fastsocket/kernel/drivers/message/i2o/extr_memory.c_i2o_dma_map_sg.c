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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct i2o_controller {scalar_t__ pae_support; TYPE_1__* pdev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int PAGE_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int dma_map_sg (int /*<<< orphan*/ *,struct scatterlist*,int,int) ; 
 int i2o_dma_high (int /*<<< orphan*/ ) ; 
 int i2o_dma_low (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

int i2o_dma_map_sg(struct i2o_controller *c, struct scatterlist *sg,
	    int sg_count, enum dma_data_direction direction, u32 ** sg_ptr)
{
	u32 sg_flags;
	u32 *mptr = *sg_ptr;

	switch (direction) {
	case DMA_TO_DEVICE:
		sg_flags = 0x14000000;
		break;
	case DMA_FROM_DEVICE:
		sg_flags = 0x10000000;
		break;
	default:
		return 0;
	}

	sg_count = dma_map_sg(&c->pdev->dev, sg, sg_count, direction);
	if (!sg_count)
		return 0;

#ifdef CONFIG_I2O_EXT_ADAPTEC_DMA64
	if ((sizeof(dma_addr_t) > 4) && c->pae_support) {
		*mptr++ = cpu_to_le32(0x7C020002);
		*mptr++ = cpu_to_le32(PAGE_SIZE);
	}
#endif

	while (sg_count-- > 0) {
		if (!sg_count)
			sg_flags |= 0xC0000000;
		*mptr++ = cpu_to_le32(sg_flags | sg_dma_len(sg));
		*mptr++ = cpu_to_le32(i2o_dma_low(sg_dma_address(sg)));
#ifdef CONFIG_I2O_EXT_ADAPTEC_DMA64
		if ((sizeof(dma_addr_t) > 4) && c->pae_support)
			*mptr++ = cpu_to_le32(i2o_dma_high(sg_dma_address(sg)));
#endif
		sg = sg_next(sg);
	}
	*sg_ptr = mptr;

	return 1;
}