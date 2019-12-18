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
struct snd_sg_buf {int dummy; } ;
struct snd_dma_buffer {scalar_t__ addr; struct snd_sg_buf* private_data; } ;
struct azx_dev {scalar_t__ frags; } ;
struct azx {int driver_caps; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int AZX_DCAPS_4K_BDLE_BOUNDARY ; 
 scalar_t__ AZX_MAX_BDL_ENTRIES ; 
 int EINVAL ; 
 int cpu_to_le32 (int) ; 
 scalar_t__ snd_sgbuf_get_addr (struct snd_sg_buf*,int) ; 
 int snd_sgbuf_get_chunk_size (struct snd_dma_buffer*,int,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int setup_bdle(struct azx *chip,
		      struct snd_dma_buffer *dmab,
		      struct azx_dev *azx_dev, u32 **bdlp,
		      int ofs, int size, int with_ioc)
{
	struct snd_sg_buf *sgbuf = dmab->private_data;
	u32 *bdl = *bdlp;

	while (size > 0) {
		dma_addr_t addr;
		int chunk;

		if (azx_dev->frags >= AZX_MAX_BDL_ENTRIES)
			return -EINVAL;

#ifdef CONFIG_SND_DMA_SGBUF
		addr = snd_sgbuf_get_addr(sgbuf, ofs);
#else
		addr = dmab->addr + ofs;
#endif
		/* program the address field of the BDL entry */
		bdl[0] = cpu_to_le32((u32)addr);
		bdl[1] = cpu_to_le32(upper_32_bits(addr));
		/* program the size field of the BDL entry */
		chunk = snd_sgbuf_get_chunk_size(dmab, ofs, size);
		/* one BDLE cannot cross 4K boundary on CTHDA chips */
		if (chip->driver_caps & AZX_DCAPS_4K_BDLE_BOUNDARY) {
			u32 remain = 0x1000 - (ofs & 0xfff);
			if (chunk > remain)
				chunk = remain;
		}
		bdl[2] = cpu_to_le32(chunk);
		/* program the IOC to enable interrupt
		 * only when the whole fragment is processed
		 */
		size -= chunk;
		bdl[3] = (size || !with_ioc) ? 0 : cpu_to_le32(0x01);
		bdl += 4;
		azx_dev->frags++;
		ofs += chunk;
	}
	*bdlp = bdl;
	return ofs;
}