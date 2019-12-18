#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_19__ {int discard; int size; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; int /*<<< orphan*/  frametype; int /*<<< orphan*/  new_chap; } ;
struct TYPE_16__ {int unfinished; int /*<<< orphan*/  list; TYPE_8__ packet_info; TYPE_12__* parser; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_17__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  start; int /*<<< orphan*/  frametype; int /*<<< orphan*/  new_chap; } ;
struct TYPE_18__ {int size; TYPE_1__ s; int /*<<< orphan*/ * data; scalar_t__ alloc; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_14__ {int /*<<< orphan*/  pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int HB_BUF_FLAG_EOF ; 
 int HB_FLAG_DISCARD ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  audioParserFlush (TYPE_3__*) ; 
 int av_parser_parse2 (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeAudio (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int decavcodecaWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                            hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;

    // libavcodec/mpeg12dec.c requires buffers to be zero padded.
    // If not zero padded, it can get stuck in an infinite loop.
    // It's likely there are other decoders that expect the same.
    if (in->data != NULL)
    {
        memset(in->data + in->size, 0, in->alloc - in->size);
    }

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        /* EOF on input stream - send it downstream & say that we're done */
        audioParserFlush(w);
        decodeAudio(pv, NULL);
        hb_buffer_list_append(&pv->list, in);
        *buf_in = NULL;
        *buf_out = hb_buffer_list_clear(&pv->list);
        return HB_WORK_DONE;
    }

    *buf_out = NULL;

    int     pos, len;
    int64_t pts = in->s.start;

    // There are a 3 scenarios that can happen here.
    // 1. The buffer contains exactly one frame of data
    // 2. The buffer contains multiple frames of data
    // 3. The buffer contains a partial frame of data
    //
    // In scenario 2, we want to be sure that the timestamps are only
    // applied to the first frame in the buffer.  Additional frames
    // in the buffer will have their timestamps computed in sync.
    //
    // In scenario 3, we need to save the ancillary buffer info of an
    // unfinished frame so it can be applied when we receive the last
    // buffer of that frame.
    if (!pv->unfinished)
    {
        // New packet, and no previous data pending
        pv->packet_info.scr_sequence = in->s.scr_sequence;
        pv->packet_info.new_chap     = in->s.new_chap;
        pv->packet_info.frametype    = in->s.frametype;
        pv->packet_info.discard      = !!(in->s.flags & HB_FLAG_DISCARD);
    }
    for (pos = 0; pos < in->size; pos += len)
    {
        uint8_t * pout = NULL;
        int       pout_len = 0;
        int64_t   parser_pts;

        if ( pv->parser != NULL )
        {
            len = av_parser_parse2(pv->parser, pv->context, &pout, &pout_len,
                                   in->data + pos, in->size - pos,
                                   pts, pts, 0 );
            parser_pts = pv->parser->pts;
            pts = AV_NOPTS_VALUE;
        }
        else
        {
            pout = in->data;
            len = pout_len = in->size;
            parser_pts = in->s.start;
        }
        if (pout != NULL && pout_len > 0)
        {
            pv->packet_info.data         = pout;
            pv->packet_info.size         = pout_len;
            pv->packet_info.pts          = parser_pts;

            decodeAudio(pv, &pv->packet_info);

            // There could have been an unfinished packet when we entered
            // decodeAudio that is now finished.  The next packet is associated
            // with the input buffer, so set it's chapter and scr info.
            pv->packet_info.scr_sequence = in->s.scr_sequence;
            pv->packet_info.discard      = !!(in->s.flags & HB_FLAG_DISCARD);
            pv->unfinished               = 0;
        }
        if (len > 0 && pout_len <= 0)
        {
            pv->unfinished               = 1;
        }
    }
    *buf_out = hb_buffer_list_clear(&pv->list);
    return HB_WORK_OK;
}