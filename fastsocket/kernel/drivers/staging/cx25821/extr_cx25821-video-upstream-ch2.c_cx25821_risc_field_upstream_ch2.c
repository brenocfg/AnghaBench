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
struct sram_channel {int /*<<< orphan*/  dma_ctl; } ;
struct cx25821_dev {size_t _channel2_upstream_select; int /*<<< orphan*/  _isNTSC_ch2; struct sram_channel* sram_channels; } ;
typedef  unsigned int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FLD_VID_FIFO_EN ; 
 unsigned int NO_SYNC_LINE ; 
 unsigned int NTSC_FIELD_HEIGHT ; 
 unsigned int NUM_NO_OPS ; 
 unsigned int RISC_EOL ; 
 unsigned int RISC_NOOP ; 
 unsigned int RISC_READ ; 
 unsigned int RISC_RESYNC ; 
 unsigned int RISC_SOL ; 
 int /*<<< orphan*/  RISC_WRITECR ; 
 scalar_t__ USE_RISC_NOOP_VIDEO ; 
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static __le32 *cx25821_risc_field_upstream_ch2(struct cx25821_dev *dev,
					       __le32 * rp,
					       dma_addr_t databuf_phys_addr,
					       unsigned int offset,
					       u32 sync_line, unsigned int bpl,
					       unsigned int lines,
					       int fifo_enable, int field_type)
{
	unsigned int line, i;
	struct sram_channel *sram_ch =
	    &dev->sram_channels[dev->_channel2_upstream_select];
	int dist_betwn_starts = bpl * 2;

	/* sync instruction */
	if (sync_line != NO_SYNC_LINE) {
		*(rp++) = cpu_to_le32(RISC_RESYNC | sync_line);
	}

	if (USE_RISC_NOOP_VIDEO) {
		for (i = 0; i < NUM_NO_OPS; i++) {
			*(rp++) = cpu_to_le32(RISC_NOOP);
		}
	}

	/* scan lines */
	for (line = 0; line < lines; line++) {
		*(rp++) = cpu_to_le32(RISC_READ | RISC_SOL | RISC_EOL | bpl);
		*(rp++) = cpu_to_le32(databuf_phys_addr + offset);
		*(rp++) = cpu_to_le32(0);	/* bits 63-32 */

		if ((lines <= NTSC_FIELD_HEIGHT)
		    || (line < (NTSC_FIELD_HEIGHT - 1))
		    || !(dev->_isNTSC_ch2)) {
			offset += dist_betwn_starts;
		}

		// check if we need to enable the FIFO after the first 4 lines
		// For the upstream video channel, the risc engine will enable the FIFO.
		if (fifo_enable && line == 3) {
			*(rp++) = RISC_WRITECR;
			*(rp++) = sram_ch->dma_ctl;
			*(rp++) = FLD_VID_FIFO_EN;
			*(rp++) = 0x00000001;
		}
	}

	return rp;
}