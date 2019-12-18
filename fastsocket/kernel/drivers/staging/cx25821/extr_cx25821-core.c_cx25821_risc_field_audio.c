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
typedef  unsigned int u32 ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int NO_SYNC_LINE ; 
 unsigned int RISC_CNT_INC ; 
 unsigned int RISC_EOL ; 
 unsigned int RISC_IRQ1 ; 
 unsigned int RISC_RESYNC ; 
 unsigned int RISC_SOL ; 
 unsigned int RISC_WRITE ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static __le32 *cx25821_risc_field_audio(__le32 * rp, struct scatterlist *sglist,
					unsigned int offset, u32 sync_line,
					unsigned int bpl, unsigned int padding,
					unsigned int lines, unsigned int lpi)
{
	struct scatterlist *sg;
	unsigned int line, todo, sol;

	/* sync instruction */
	if (sync_line != NO_SYNC_LINE)
		*(rp++) = cpu_to_le32(RISC_RESYNC | sync_line);

	/* scan lines */
	sg = sglist;
	for (line = 0; line < lines; line++) {
		while (offset && offset >= sg_dma_len(sg)) {
			offset -= sg_dma_len(sg);
			sg++;
		}

		if (lpi && line > 0 && !(line % lpi))
			sol = RISC_SOL | RISC_IRQ1 | RISC_CNT_INC;
		else
			sol = RISC_SOL;

		if (bpl <= sg_dma_len(sg) - offset) {
			/* fits into current chunk */
			*(rp++) =
			    cpu_to_le32(RISC_WRITE | sol | RISC_EOL | bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += bpl;
		} else {
			/* scanline needs to be split */
			todo = bpl;
			*(rp++) = cpu_to_le32(RISC_WRITE | sol |
					      (sg_dma_len(sg) - offset));
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			todo -= (sg_dma_len(sg) - offset);
			offset = 0;
			sg++;
			while (todo > sg_dma_len(sg)) {
				*(rp++) = cpu_to_le32(RISC_WRITE |
						      sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
				todo -= sg_dma_len(sg);
				sg++;
			}
			*(rp++) = cpu_to_le32(RISC_WRITE | RISC_EOL | todo);
			*(rp++) = cpu_to_le32(sg_dma_address(sg));
			*(rp++) = cpu_to_le32(0);	/* bits 63-32 */
			offset += todo;
		}
		offset += padding;
	}

	return rp;
}