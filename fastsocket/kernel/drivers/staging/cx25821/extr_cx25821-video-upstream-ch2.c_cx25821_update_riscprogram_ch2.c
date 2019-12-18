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
struct cx25821_dev {unsigned int _data_buf_phys_addr_ch2; int /*<<< orphan*/  _isNTSC_ch2; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int NTSC_FIELD_HEIGHT ; 
 unsigned int NUM_NO_OPS ; 
 unsigned int RISC_EOL ; 
 unsigned int RISC_NOOP ; 
 unsigned int RISC_READ ; 
 unsigned int RISC_RESYNC ; 
 unsigned int RISC_SOL ; 
 scalar_t__ USE_RISC_NOOP_VIDEO ; 
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static __le32 *cx25821_update_riscprogram_ch2(struct cx25821_dev *dev,
					      __le32 * rp, unsigned int offset,
					      unsigned int bpl, u32 sync_line,
					      unsigned int lines,
					      int fifo_enable, int field_type)
{
	unsigned int line, i;
	int dist_betwn_starts = bpl * 2;

	*(rp++) = cpu_to_le32(RISC_RESYNC | sync_line);

	if (USE_RISC_NOOP_VIDEO) {
		for (i = 0; i < NUM_NO_OPS; i++) {
			*(rp++) = cpu_to_le32(RISC_NOOP);
		}
	}

	/* scan lines */
	for (line = 0; line < lines; line++) {
		*(rp++) = cpu_to_le32(RISC_READ | RISC_SOL | RISC_EOL | bpl);
		*(rp++) = cpu_to_le32(dev->_data_buf_phys_addr_ch2 + offset);
		*(rp++) = cpu_to_le32(0);	/* bits 63-32 */

		if ((lines <= NTSC_FIELD_HEIGHT)
		    || (line < (NTSC_FIELD_HEIGHT - 1))
		    || !(dev->_isNTSC_ch2)) {
			offset += dist_betwn_starts;
		}
	}

	return rp;
}