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
typedef  int /*<<< orphan*/  u32 ;
struct pvr2_hdw {unsigned int* cmd_buffer; } ;

/* Variables and functions */
 unsigned int FX2CMD_MEM_READ_64BYTES ; 
 unsigned int FX2CMD_MEM_READ_DWORD ; 
 int /*<<< orphan*/  PVR2_COMPOSE_LE (unsigned int*,unsigned int) ; 
 int pvr2_send_request (struct pvr2_hdw*,unsigned int*,int,unsigned int*,int) ; 

__attribute__((used)) static int pvr2_encoder_read_words(struct pvr2_hdw *hdw,
				   unsigned int offs,
				   u32 *data, unsigned int dlen)
{
	unsigned int idx;
	int ret;
	unsigned int chunkCnt;

	/*

	Format: First byte must be 0x02 (status check) or 0x28 (read
	back block of 32 bit words).  Next 6 bytes must be zero,
	followed by a single byte of MBOX_BASE+offset for portion to
	be read.  Returned data is packed set of 32 bits words that
	were read.

	*/

	while (dlen) {
		chunkCnt = 16;
		if (chunkCnt > dlen) chunkCnt = dlen;
		if (chunkCnt < 16) chunkCnt = 1;
		hdw->cmd_buffer[0] =
			((chunkCnt == 1) ?
			 FX2CMD_MEM_READ_DWORD : FX2CMD_MEM_READ_64BYTES);
		hdw->cmd_buffer[1] = 0;
		hdw->cmd_buffer[2] = 0;
		hdw->cmd_buffer[3] = 0;
		hdw->cmd_buffer[4] = 0;
		hdw->cmd_buffer[5] = ((offs>>16) & 0xffu);
		hdw->cmd_buffer[6] = ((offs>>8) & 0xffu);
		hdw->cmd_buffer[7] = (offs & 0xffu);
		ret = pvr2_send_request(hdw,
					hdw->cmd_buffer,8,
					hdw->cmd_buffer,
					(chunkCnt == 1 ? 4 : 16 * 4));
		if (ret) return ret;

		for (idx = 0; idx < chunkCnt; idx++) {
			data[idx] = PVR2_COMPOSE_LE(hdw->cmd_buffer,idx*4);
		}
		data += chunkCnt;
		dlen -= chunkCnt;
		offs += chunkCnt;
	}

	return 0;
}