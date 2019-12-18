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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct ivtv_user_dma {int SG_length; TYPE_1__* SGarray; struct scatterlist* SGlist; } ;
struct TYPE_2__ {void* dst; void* src; void* size; } ;

/* Variables and functions */
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 

void ivtv_udma_fill_sg_array (struct ivtv_user_dma *dma, u32 buffer_offset, u32 buffer_offset_2, u32 split) {
	int i;
	struct scatterlist *sg;

	for (i = 0, sg = dma->SGlist; i < dma->SG_length; i++, sg++) {
		dma->SGarray[i].size = cpu_to_le32(sg_dma_len(sg));
		dma->SGarray[i].src = cpu_to_le32(sg_dma_address(sg));
		dma->SGarray[i].dst = cpu_to_le32(buffer_offset);
		buffer_offset += sg_dma_len(sg);

		split -= sg_dma_len(sg);
		if (split == 0)
			buffer_offset = buffer_offset_2;
	}
}