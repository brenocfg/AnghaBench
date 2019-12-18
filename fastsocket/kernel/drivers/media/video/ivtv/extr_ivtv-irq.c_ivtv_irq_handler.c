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
typedef  int u8 ;
typedef  int u32 ;
struct ivtv_stream {scalar_t__ type; int /*<<< orphan*/  s_flags; } ;
struct ivtv {int irqmask; int last_vsync_field; int irq_rr_idx; int /*<<< orphan*/  dma_reg_lock; int /*<<< orphan*/  irq_work_queue; int /*<<< orphan*/  irq_work_queues; int /*<<< orphan*/  i_flags; struct ivtv_stream* streams; int /*<<< orphan*/  eos_waitq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_IRQ (char*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_IRQ (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*,int) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_MPG ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_EOS ; 
 int /*<<< orphan*/  IVTV_F_I_HAVE_WORK ; 
 int /*<<< orphan*/  IVTV_F_I_PIO ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA_PENDING ; 
 int /*<<< orphan*/  IVTV_F_S_DMA_PENDING ; 
 int /*<<< orphan*/  IVTV_F_S_PIO_PENDING ; 
 int IVTV_IRQ_DEC_AUD_MODE_CHG ; 
 int IVTV_IRQ_DEC_DATA_REQ ; 
 int IVTV_IRQ_DEC_DMA_COMPLETE ; 
 int IVTV_IRQ_DEC_VBI_RE_INSERT ; 
 int IVTV_IRQ_DEC_VSYNC ; 
 int IVTV_IRQ_DMA ; 
 int IVTV_IRQ_DMA_ERR ; 
 int IVTV_IRQ_DMA_READ ; 
 int IVTV_IRQ_ENC_DMA_COMPLETE ; 
 int IVTV_IRQ_ENC_EOS ; 
 int IVTV_IRQ_ENC_PIO_COMPLETE ; 
 int IVTV_IRQ_ENC_START_CAP ; 
 int IVTV_IRQ_ENC_VBI_CAP ; 
 int IVTV_IRQ_ENC_VIM_RST ; 
 int IVTV_MAX_STREAMS ; 
 int /*<<< orphan*/  IVTV_REG_DEC_LINE_FIELD ; 
 int /*<<< orphan*/  IVTV_REG_IRQSTATUS ; 
 int /*<<< orphan*/  ivtv_dma_dec_start (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_dma_enc_start (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_irq_dec_data_req (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_dec_vbi_reinsert (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_dma_err (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_dma_read (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_enc_dma_complete (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_enc_pio_complete (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_enc_start_cap (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_enc_vbi_cap (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_irq_vsync (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_udma_start (struct ivtv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

irqreturn_t ivtv_irq_handler(int irq, void *dev_id)
{
	struct ivtv *itv = (struct ivtv *)dev_id;
	u32 combo;
	u32 stat;
	int i;
	u8 vsync_force = 0;

	spin_lock(&itv->dma_reg_lock);
	/* get contents of irq status register */
	stat = read_reg(IVTV_REG_IRQSTATUS);

	combo = ~itv->irqmask & stat;

	/* Clear out IRQ */
	if (combo) write_reg(combo, IVTV_REG_IRQSTATUS);

	if (0 == combo) {
		/* The vsync interrupt is unusual and clears itself. If we
		 * took too long, we may have missed it. Do some checks
		 */
		if (~itv->irqmask & IVTV_IRQ_DEC_VSYNC) {
			/* vsync is enabled, see if we're in a new field */
			if ((itv->last_vsync_field & 1) !=
			    (read_reg(IVTV_REG_DEC_LINE_FIELD) & 1)) {
				/* New field, looks like we missed it */
				IVTV_DEBUG_YUV("VSync interrupt missed %d\n",
				       read_reg(IVTV_REG_DEC_LINE_FIELD) >> 16);
				vsync_force = 1;
			}
		}

		if (!vsync_force) {
			/* No Vsync expected, wasn't for us */
			spin_unlock(&itv->dma_reg_lock);
			return IRQ_NONE;
		}
	}

	/* Exclude interrupts noted below from the output, otherwise the log is flooded with
	   these messages */
	if (combo & ~0xff6d0400)
		IVTV_DEBUG_HI_IRQ("======= valid IRQ bits: 0x%08x ======\n", combo);

	if (combo & IVTV_IRQ_DEC_DMA_COMPLETE) {
		IVTV_DEBUG_HI_IRQ("DEC DMA COMPLETE\n");
	}

	if (combo & IVTV_IRQ_DMA_READ) {
		ivtv_irq_dma_read(itv);
	}

	if (combo & IVTV_IRQ_ENC_DMA_COMPLETE) {
		ivtv_irq_enc_dma_complete(itv);
	}

	if (combo & IVTV_IRQ_ENC_PIO_COMPLETE) {
		ivtv_irq_enc_pio_complete(itv);
	}

	if (combo & IVTV_IRQ_DMA_ERR) {
		ivtv_irq_dma_err(itv);
	}

	if (combo & IVTV_IRQ_ENC_START_CAP) {
		ivtv_irq_enc_start_cap(itv);
	}

	if (combo & IVTV_IRQ_ENC_VBI_CAP) {
		ivtv_irq_enc_vbi_cap(itv);
	}

	if (combo & IVTV_IRQ_DEC_VBI_RE_INSERT) {
		ivtv_irq_dec_vbi_reinsert(itv);
	}

	if (combo & IVTV_IRQ_ENC_EOS) {
		IVTV_DEBUG_IRQ("ENC EOS\n");
		set_bit(IVTV_F_I_EOS, &itv->i_flags);
		wake_up(&itv->eos_waitq);
	}

	if (combo & IVTV_IRQ_DEC_DATA_REQ) {
		ivtv_irq_dec_data_req(itv);
	}

	/* Decoder Vertical Sync - We can't rely on 'combo', so check if vsync enabled */
	if (~itv->irqmask & IVTV_IRQ_DEC_VSYNC) {
		ivtv_irq_vsync(itv);
	}

	if (combo & IVTV_IRQ_ENC_VIM_RST) {
		IVTV_DEBUG_IRQ("VIM RST\n");
		/*ivtv_vapi(itv, CX2341X_ENC_REFRESH_INPUT, 0); */
	}

	if (combo & IVTV_IRQ_DEC_AUD_MODE_CHG) {
		IVTV_DEBUG_INFO("Stereo mode changed\n");
	}

	if ((combo & IVTV_IRQ_DMA) && !test_bit(IVTV_F_I_DMA, &itv->i_flags)) {
		itv->irq_rr_idx++;
		for (i = 0; i < IVTV_MAX_STREAMS; i++) {
			int idx = (i + itv->irq_rr_idx) % IVTV_MAX_STREAMS;
			struct ivtv_stream *s = &itv->streams[idx];

			if (!test_and_clear_bit(IVTV_F_S_DMA_PENDING, &s->s_flags))
				continue;
			if (s->type >= IVTV_DEC_STREAM_TYPE_MPG)
				ivtv_dma_dec_start(s);
			else
				ivtv_dma_enc_start(s);
			break;
		}

		if (i == IVTV_MAX_STREAMS &&
		    test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags))
			ivtv_udma_start(itv);
	}

	if ((combo & IVTV_IRQ_DMA) && !test_bit(IVTV_F_I_PIO, &itv->i_flags)) {
		itv->irq_rr_idx++;
		for (i = 0; i < IVTV_MAX_STREAMS; i++) {
			int idx = (i + itv->irq_rr_idx) % IVTV_MAX_STREAMS;
			struct ivtv_stream *s = &itv->streams[idx];

			if (!test_and_clear_bit(IVTV_F_S_PIO_PENDING, &s->s_flags))
				continue;
			if (s->type == IVTV_DEC_STREAM_TYPE_VBI || s->type < IVTV_DEC_STREAM_TYPE_MPG)
				ivtv_dma_enc_start(s);
			break;
		}
	}

	if (test_and_clear_bit(IVTV_F_I_HAVE_WORK, &itv->i_flags)) {
		queue_work(itv->irq_work_queues, &itv->irq_work_queue);
	}

	spin_unlock(&itv->dma_reg_lock);

	/* If we've just handled a 'forced' vsync, it's safest to say it
	 * wasn't ours. Another device may have triggered it at just
	 * the right time.
	 */
	return vsync_force ? IRQ_NONE : IRQ_HANDLED;
}