#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* int64_t ;
struct TYPE_19__ {scalar_t__ new_chap; int discard; int size; int /*<<< orphan*/  frametype; int /*<<< orphan*/  scr_sequence; void* dts; void* pts; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {scalar_t__ new_chap; scalar_t__ chap_time; scalar_t__ last_pts; int unfinished; int /*<<< orphan*/  list; TYPE_2__ packet_info; TYPE_15__* context; int /*<<< orphan*/  codec; TYPE_14__* parser; int /*<<< orphan*/  chap_scr; int /*<<< orphan*/ * palette; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_21__ {int /*<<< orphan*/  frame_count; TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_work_object_t ;
struct TYPE_18__ {int flags; scalar_t__ start; scalar_t__ new_chap; int /*<<< orphan*/  frametype; int /*<<< orphan*/  scr_sequence; void* renderOffset; } ;
struct TYPE_22__ {int size; TYPE_1__ s; int /*<<< orphan*/ * data; int /*<<< orphan*/ * palette; scalar_t__ alloc; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_17__ {int codec_id; int /*<<< orphan*/ * codec; } ;
struct TYPE_16__ {void* dts; void* pts; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int HB_BUF_FLAG_EOF ; 
 int HB_FLAG_DISCARD ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int av_parser_parse2 (TYPE_14__*,TYPE_15__*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_find_decoder (int) ; 
 scalar_t__ decodeFrame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int decodePacket (TYPE_4__*) ; 
 int /*<<< orphan*/  hb_buffer_dup (TYPE_5__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  videoParserFlush (TYPE_4__*) ; 

__attribute__((used)) static int decavcodecvWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                            hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv     = w->private_data;
    hb_buffer_t       * in     = *buf_in;
    int                 result = HB_WORK_OK;

    *buf_out = NULL;

    // libavcodec/mpeg12dec.c requires buffers to be zero padded.
    // If not zero padded, it can get stuck in an infinite loop.
    // It's likely there are other decoders that expect the same.
    if (in->data != NULL)
    {
        memset(in->data + in->size, 0, in->alloc - in->size);
    }
    if (in->palette != NULL)
    {
        pv->palette = in->palette;
        in->palette = NULL;
    }

    /* if we got an empty buffer signaling end-of-stream send it downstream */
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        if (pv->context != NULL && pv->context->codec != NULL)
        {
            videoParserFlush(w);
            while (decodeFrame(pv, NULL))
            {
                continue;
            }
        }
        hb_buffer_list_append(&pv->list, hb_buffer_dup(in));
        *buf_out = hb_buffer_list_clear(&pv->list);
        return HB_WORK_DONE;
    }

    /*
     * The following loop is a do..while because we need to handle both
     * data & the flush at the end (signaled by size=0). At the end there's
     * generally a frame in the parser & one or more frames in the decoder
     * (depending on the bframes setting).
     */
    int      pos, len;
    int64_t  pts = in->s.start;
    int64_t  dts = in->s.renderOffset;

    if (in->s.new_chap > 0)
    {
        pv->new_chap = in->s.new_chap;
        pv->chap_scr = in->s.scr_sequence;
        if (in->s.start != AV_NOPTS_VALUE)
        {
            pv->chap_time = in->s.start;
        }
        else
        {
            pv->chap_time = pv->last_pts + 1;
        }
    }
    if (in->s.start != AV_NOPTS_VALUE)
    {
        pv->last_pts = in->s.start;
    }

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
        int64_t   parser_pts, parser_dts;

        if (pv->parser)
        {
            int codec_id = pv->context->codec_id;
            len = av_parser_parse2(pv->parser, pv->context, &pout, &pout_len,
                                   in->data + pos, in->size - pos,
                                   pts, dts, 0 );
            parser_pts = pv->parser->pts;
            parser_dts = pv->parser->dts;
            pts = AV_NOPTS_VALUE;
            dts = AV_NOPTS_VALUE;

            if (codec_id != pv->context->codec_id)
            {
                // The parser has decided to change the decoder underneath
                // us.  Update our context to match.  This can happen
                // for MPEG-1/2 video, perhaps others
                pv->codec = avcodec_find_decoder(pv->context->codec_id);
            }
        }
        else
        {
            pout = in->data;
            len = pout_len = in->size;
            parser_pts = pts;
            parser_dts = dts;
        }

        if (pout != NULL && pout_len > 0)
        {
            pv->packet_info.data         = pout;
            pv->packet_info.size         = pout_len;
            pv->packet_info.pts          = parser_pts;
            pv->packet_info.dts          = parser_dts;

            result = decodePacket(w);
            if (result != HB_WORK_OK)
            {
                break;
            }
            w->frame_count++;

            // There could have been an unfinished packet that is now finished.
            // The next packet is associated with the input buffer, so set
            // it's chapter and scr info.
            pv->packet_info.scr_sequence = in->s.scr_sequence;
            pv->packet_info.new_chap     = in->s.new_chap;
            pv->packet_info.frametype    = in->s.frametype;
            pv->packet_info.discard      = !!(in->s.flags & HB_FLAG_DISCARD);
            pv->unfinished               = 0;
        }
        if (len > 0 && pout_len <= 0)
        {
            pv->unfinished = 1;
        }
    }
    *buf_out = hb_buffer_list_clear(&pv->list);

    return result;
}