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
struct ivtv_stream {scalar_t__ type; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; } ;
struct ivtv {int cur_pio_stream; int /*<<< orphan*/  dma_waitq; struct ivtv_stream* streams; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SCHED_DMA_TO_HOST ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_IRQ (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_MPG ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_PCM ; 
 size_t IVTV_ENC_STREAM_TYPE_VBI ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_PIO ; 
 int /*<<< orphan*/  IVTV_F_S_DMA_HAS_VBI ; 
 int IVTV_MAX_STREAMS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_post (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_irq_enc_pio_complete(struct ivtv *itv)
{
	struct ivtv_stream *s;

	if (itv->cur_pio_stream < 0 || itv->cur_pio_stream >= IVTV_MAX_STREAMS) {
		itv->cur_pio_stream = -1;
		return;
	}
	s = &itv->streams[itv->cur_pio_stream];
	IVTV_DEBUG_HI_IRQ("ENC PIO COMPLETE %s\n", s->name);
	clear_bit(IVTV_F_I_PIO, &itv->i_flags);
	itv->cur_pio_stream = -1;
	dma_post(s);
	if (s->type == IVTV_ENC_STREAM_TYPE_MPG)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 0);
	else if (s->type == IVTV_ENC_STREAM_TYPE_YUV)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 1);
	else if (s->type == IVTV_ENC_STREAM_TYPE_PCM)
		ivtv_vapi(itv, CX2341X_ENC_SCHED_DMA_TO_HOST, 3, 0, 0, 2);
	clear_bit(IVTV_F_I_PIO, &itv->i_flags);
	if (test_and_clear_bit(IVTV_F_S_DMA_HAS_VBI, &s->s_flags)) {
		s = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
		dma_post(s);
	}
	wake_up(&itv->dma_waitq);
}