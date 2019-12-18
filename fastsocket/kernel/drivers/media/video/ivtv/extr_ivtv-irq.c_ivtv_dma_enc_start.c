#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bytesused; } ;
struct ivtv_stream {size_t sg_pending_size; scalar_t__ type; scalar_t__ buffers; int sg_processing_size; int /*<<< orphan*/  pending_pts; int /*<<< orphan*/  dma_pts; int /*<<< orphan*/  pending_backup; int /*<<< orphan*/  dma_backup; int /*<<< orphan*/  pending_offset; int /*<<< orphan*/  dma_offset; scalar_t__ sg_processed; TYPE_1__* sg_pending; int /*<<< orphan*/  sg_processing; int /*<<< orphan*/  dma_xfer_cnt; int /*<<< orphan*/  name; int /*<<< orphan*/  s_flags; TYPE_2__ q_predma; int /*<<< orphan*/  q_dma; struct ivtv* itv; } ;
struct ivtv_sg_host_element {int dummy; } ;
struct ivtv {scalar_t__ cur_pio_stream; scalar_t__ cur_dma_stream; int /*<<< orphan*/  i_flags; scalar_t__ dma_retries; struct ivtv_stream* streams; } ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_HI_DMA (char*,char*,...) ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_MPG ; 
 size_t IVTV_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_HAVE_WORK ; 
 int /*<<< orphan*/  IVTV_F_I_PIO ; 
 int /*<<< orphan*/  IVTV_F_I_WORK_HANDLER_PIO ; 
 int /*<<< orphan*/  IVTV_F_S_DMA_HAS_VBI ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_dma_enc_start_xfer (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_queue_move (struct ivtv_stream*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ivtv_use_dma (struct ivtv_stream*) ; 
 scalar_t__ ivtv_use_pio (struct ivtv_stream*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_dma_enc_start(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;
	struct ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	int i;

	IVTV_DEBUG_HI_DMA("start %s for %s\n", ivtv_use_dma(s) ? "DMA" : "PIO", s->name);

	if (s->q_predma.bytesused)
		ivtv_queue_move(s, &s->q_predma, NULL, &s->q_dma, s->q_predma.bytesused);

	if (ivtv_use_dma(s))
		s->sg_pending[s->sg_pending_size - 1].size += 256;

	/* If this is an MPEG stream, and VBI data is also pending, then append the
	   VBI DMA to the MPEG DMA and transfer both sets of data at once.

	   VBI DMA is a second class citizen compared to MPEG and mixing them together
	   will confuse the firmware (the end of a VBI DMA is seen as the end of a
	   MPEG DMA, thus effectively dropping an MPEG frame). So instead we make
	   sure we only use the MPEG DMA to transfer the VBI DMA if both are in
	   use. This way no conflicts occur. */
	clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags);
	if (s->type == IVTV_ENC_STREAM_TYPE_MPG && s_vbi->sg_pending_size &&
			s->sg_pending_size + s_vbi->sg_pending_size <= s->buffers) {
		ivtv_queue_move(s_vbi, &s_vbi->q_predma, NULL, &s_vbi->q_dma, s_vbi->q_predma.bytesused);
		if (ivtv_use_dma(s_vbi))
			s_vbi->sg_pending[s_vbi->sg_pending_size - 1].size += 256;
		for (i = 0; i < s_vbi->sg_pending_size; i++) {
			s->sg_pending[s->sg_pending_size++] = s_vbi->sg_pending[i];
		}
		s_vbi->dma_offset = s_vbi->pending_offset;
		s_vbi->sg_pending_size = 0;
		s_vbi->dma_xfer_cnt++;
		set_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags);
		IVTV_DEBUG_HI_DMA("include DMA for %s\n", s_vbi->name);
	}

	s->dma_xfer_cnt++;
	memcpy(s->sg_processing, s->sg_pending, sizeof(struct ivtv_sg_host_element) * s->sg_pending_size);
	s->sg_processing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_processed = 0;
	s->dma_offset = s->pending_offset;
	s->dma_backup = s->pending_backup;
	s->dma_pts = s->pending_pts;

	if (ivtv_use_pio(s)) {
		set_bit(IVTV_F_I_WORK_HANDLER_PIO, &itv->i_flags);
		set_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags);
		set_bit(IVTV_F_I_PIO, &itv->i_flags);
		itv->cur_pio_stream = s->type;
	}
	else {
		itv->dma_retries = 0;
		ivtv_dma_enc_start_xfer(s);
		set_bit(IVTV_F_I_DMA, &itv->i_flags);
		itv->cur_dma_stream = s->type;
	}
}