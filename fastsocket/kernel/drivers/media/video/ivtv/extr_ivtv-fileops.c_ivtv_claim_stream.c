#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ivtv_stream {int id; int /*<<< orphan*/  s_flags; } ;
struct ivtv_open_id {int open_id; struct ivtv* itv; } ;
struct TYPE_2__ {scalar_t__ insert_mpeg; } ;
struct ivtv {struct ivtv_stream* streams; TYPE_1__ vbi; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,...) ; 
 int IVTV_DEC_STREAM_TYPE_MPG ; 
 int IVTV_DEC_STREAM_TYPE_VBI ; 
 int IVTV_ENC_STREAM_TYPE_MPG ; 
 int IVTV_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_S_CLAIMED ; 
 int /*<<< orphan*/  IVTV_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  IVTV_IRQ_DEC_VBI_RE_INSERT ; 
 int /*<<< orphan*/  ivtv_clear_irq_mask (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_raw_vbi (struct ivtv*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ivtv_claim_stream(struct ivtv_open_id *id, int type)
{
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[type];
	struct ivtv_stream *s_vbi;
	int vbi_type;

	if (test_and_set_bit(IVTV_F_S_CLAIMED, &s->s_flags)) {
		/* someone already claimed this stream */
		if (s->id == id->open_id) {
			/* yes, this file descriptor did. So that's OK. */
			return 0;
		}
		if (s->id == -1 && (type == IVTV_DEC_STREAM_TYPE_VBI ||
					 type == IVTV_ENC_STREAM_TYPE_VBI)) {
			/* VBI is handled already internally, now also assign
			   the file descriptor to this stream for external
			   reading of the stream. */
			s->id = id->open_id;
			IVTV_DEBUG_INFO("Start Read VBI\n");
			return 0;
		}
		/* someone else is using this stream already */
		IVTV_DEBUG_INFO("Stream %d is busy\n", type);
		return -EBUSY;
	}
	s->id = id->open_id;
	if (type == IVTV_DEC_STREAM_TYPE_VBI) {
		/* Enable reinsertion interrupt */
		ivtv_clear_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);
	}

	/* IVTV_DEC_STREAM_TYPE_MPG needs to claim IVTV_DEC_STREAM_TYPE_VBI,
	   IVTV_ENC_STREAM_TYPE_MPG needs to claim IVTV_ENC_STREAM_TYPE_VBI
	   (provided VBI insertion is on and sliced VBI is selected), for all
	   other streams we're done */
	if (type == IVTV_DEC_STREAM_TYPE_MPG) {
		vbi_type = IVTV_DEC_STREAM_TYPE_VBI;
	} else if (type == IVTV_ENC_STREAM_TYPE_MPG &&
		   itv->vbi.insert_mpeg && !ivtv_raw_vbi(itv)) {
		vbi_type = IVTV_ENC_STREAM_TYPE_VBI;
	} else {
		return 0;
	}
	s_vbi = &itv->streams[vbi_type];

	if (!test_and_set_bit(IVTV_F_S_CLAIMED, &s_vbi->s_flags)) {
		/* Enable reinsertion interrupt */
		if (vbi_type == IVTV_DEC_STREAM_TYPE_VBI)
			ivtv_clear_irq_mask(itv, IVTV_IRQ_DEC_VBI_RE_INSERT);
	}
	/* mark that it is used internally */
	set_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags);
	return 0;
}