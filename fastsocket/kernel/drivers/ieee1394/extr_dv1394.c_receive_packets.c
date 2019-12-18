#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kvirt; } ;
struct video_card {int n_frames; int /*<<< orphan*/  spinlock; TYPE_4__ packet_buf; struct frame** frames; } ;
struct packet {int dummy; } ;
struct frame {int descriptor_pool_dma; int frame_num; void** frame_end_branch; struct DMA_descriptor_block* descriptor_pool; } ;
struct TYPE_7__ {void** q; } ;
struct TYPE_5__ {TYPE_3__ il; } ;
struct TYPE_6__ {TYPE_1__ in; } ;
struct DMA_descriptor_block {TYPE_2__ u; } ;
typedef  int dma_addr_t ;
typedef  void* __le32 ;

/* Variables and functions */
 int MAX_PACKETS ; 
 void* cpu_to_le32 (int) ; 
 int dma_region_offset_to_bus (TYPE_4__*,unsigned long) ; 
 int /*<<< orphan*/  fill_input_last (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void receive_packets(struct video_card *video)
{
	struct DMA_descriptor_block *block = NULL;
	dma_addr_t block_dma = 0;
	struct packet *data = NULL;
	dma_addr_t data_dma = 0;
	__le32 *last_branch_address = NULL;
	unsigned long irq_flags;
	int want_interrupt = 0;
	struct frame *f = NULL;
	int i, j;

	spin_lock_irqsave(&video->spinlock, irq_flags);

	for (j = 0; j < video->n_frames; j++) {

		/* connect frames */
		if (j > 0 && f != NULL && f->frame_end_branch != NULL)
			*(f->frame_end_branch) = cpu_to_le32(video->frames[j]->descriptor_pool_dma | 1); /* set Z=1 */

		f = video->frames[j];

		for (i = 0; i < MAX_PACKETS; i++) {
			/* locate a descriptor block and packet from the buffer */
			block = &(f->descriptor_pool[i]);
			block_dma = ((unsigned long) block - (unsigned long) f->descriptor_pool) + f->descriptor_pool_dma;

			data = ((struct packet*)video->packet_buf.kvirt) + f->frame_num * MAX_PACKETS + i;
			data_dma = dma_region_offset_to_bus( &video->packet_buf,
							     ((unsigned long) data - (unsigned long) video->packet_buf.kvirt) );

			/* setup DMA descriptor block */
			want_interrupt = ((i % (MAX_PACKETS/2)) == 0 || i == (MAX_PACKETS-1));
			fill_input_last( &(block->u.in.il), want_interrupt, 512, data_dma);

			/* link descriptors */
			last_branch_address = f->frame_end_branch;

			if (last_branch_address != NULL)
				*(last_branch_address) = cpu_to_le32(block_dma | 1); /* set Z=1 */

			f->frame_end_branch = &(block->u.in.il.q[2]);
		}

	} /* next j */

	spin_unlock_irqrestore(&video->spinlock, irq_flags);

}