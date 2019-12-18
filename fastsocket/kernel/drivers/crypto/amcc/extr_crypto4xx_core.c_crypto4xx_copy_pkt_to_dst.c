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
typedef  size_t u32 ;
struct scatterlist {size_t length; int /*<<< orphan*/  offset; } ;
struct pd_uinfo {size_t first_sd; } ;
struct crypto4xx_device {size_t scatter_buffer_size; TYPE_1__* core_dev; } ;
struct ce_pd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ crypto4xx_fill_one_page (struct crypto4xx_device*,int /*<<< orphan*/ *,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void crypto4xx_copy_pkt_to_dst(struct crypto4xx_device *dev,
				      struct ce_pd *pd,
				      struct pd_uinfo *pd_uinfo,
				      u32 nbytes,
				      struct scatterlist *dst)
{
	dma_addr_t addr;
	u32 this_sd;
	u32 offset;
	u32 len;
	u32 i;
	u32 sg_len;
	struct scatterlist *sg;

	this_sd = pd_uinfo->first_sd;
	offset = 0;
	i = 0;

	while (nbytes) {
		sg = &dst[i];
		sg_len = sg->length;
		addr = dma_map_page(dev->core_dev->device, sg_page(sg),
				sg->offset, sg->length, DMA_TO_DEVICE);

		if (offset == 0) {
			len = (nbytes <= sg->length) ? nbytes : sg->length;
			while (crypto4xx_fill_one_page(dev, &addr, &len,
				&this_sd, &offset, &nbytes))
				;
			if (!nbytes)
				return;
			i++;
		} else {
			len = (nbytes <= (dev->scatter_buffer_size - offset)) ?
				nbytes : (dev->scatter_buffer_size - offset);
			len = (sg->length < len) ? sg->length : len;
			while (crypto4xx_fill_one_page(dev, &addr, &len,
					       &this_sd, &offset, &nbytes))
				;
			if (!nbytes)
				return;
			sg_len -= len;
			if (sg_len) {
				addr += len;
				while (crypto4xx_fill_one_page(dev, &addr,
					&sg_len, &this_sd, &offset, &nbytes))
					;
			}
			i++;
		}
	}
}