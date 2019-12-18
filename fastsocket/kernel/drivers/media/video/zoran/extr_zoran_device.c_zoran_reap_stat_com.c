#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int length; int seq; int /*<<< orphan*/  timestamp; } ;
struct zoran_buffer {int /*<<< orphan*/  state; TYPE_2__ bs; } ;
struct TYPE_6__ {int TmpDcm; } ;
struct TYPE_4__ {struct zoran_buffer* buffer; } ;
struct zoran {scalar_t__ codec_mode; unsigned int jpg_seq_num; size_t jpg_dma_tail; size_t jpg_dma_head; int jpg_err_shift; int* jpg_pend; int jpg_err_seq; TYPE_3__ jpg_settings; TYPE_1__ jpg_buffers; int /*<<< orphan*/ * stat_com; } ;

/* Variables and functions */
 size_t BUZ_MASK_FRAME ; 
 int BUZ_MASK_STAT_COM ; 
 scalar_t__ BUZ_MODE_MOTION_COMPRESS ; 
 scalar_t__ BUZ_MODE_MOTION_DECOMPRESS ; 
 int /*<<< orphan*/  BUZ_STATE_DONE ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zoran_reap_stat_com (struct zoran *zr)
{
	/* move frames from DMA queue to done queue */

	int i;
	u32 stat_com;
	unsigned int seq;
	unsigned int dif;
	struct zoran_buffer *buffer;
	int frame;

	/* In motion decompress we don't have a hardware frame counter,
	 * we just count the interrupts here */

	if (zr->codec_mode == BUZ_MODE_MOTION_DECOMPRESS) {
		zr->jpg_seq_num++;
	}
	while (zr->jpg_dma_tail < zr->jpg_dma_head) {
		if (zr->jpg_settings.TmpDcm == 1)
			i = (zr->jpg_dma_tail -
			     zr->jpg_err_shift) & BUZ_MASK_STAT_COM;
		else
			i = ((zr->jpg_dma_tail -
			      zr->jpg_err_shift) & 1) * 2 + 1;

		stat_com = le32_to_cpu(zr->stat_com[i]);

		if ((stat_com & 1) == 0) {
			return;
		}
		frame = zr->jpg_pend[zr->jpg_dma_tail & BUZ_MASK_FRAME];
		buffer = &zr->jpg_buffers.buffer[frame];
		do_gettimeofday(&buffer->bs.timestamp);

		if (zr->codec_mode == BUZ_MODE_MOTION_COMPRESS) {
			buffer->bs.length = (stat_com & 0x7fffff) >> 1;

			/* update sequence number with the help of the counter in stat_com */

			seq = ((stat_com >> 24) + zr->jpg_err_seq) & 0xff;
			dif = (seq - zr->jpg_seq_num) & 0xff;
			zr->jpg_seq_num += dif;
		} else {
			buffer->bs.length = 0;
		}
		buffer->bs.seq =
		    zr->jpg_settings.TmpDcm ==
		    2 ? (zr->jpg_seq_num >> 1) : zr->jpg_seq_num;
		buffer->state = BUZ_STATE_DONE;

		zr->jpg_dma_tail++;
	}
}