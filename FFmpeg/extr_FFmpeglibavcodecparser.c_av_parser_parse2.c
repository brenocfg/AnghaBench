#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* int64_t ;
typedef  int /*<<< orphan*/  dummy_buf ;
struct TYPE_11__ {scalar_t__ codec_id; scalar_t__ codec_type; scalar_t__ field_order; } ;
struct TYPE_10__ {int flags; scalar_t__ next_frame_offset; scalar_t__ cur_offset; scalar_t__* cur_frame_end; size_t cur_frame_start_index; scalar_t__* cur_frame_offset; int fetch_timestamp; scalar_t__ field_order; scalar_t__ frame_offset; TYPE_1__* parser; int /*<<< orphan*/  pos; int /*<<< orphan*/  last_pos; int /*<<< orphan*/  dts; int /*<<< orphan*/  last_dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  last_pts; void** cur_frame_pos; void** cur_frame_dts; void** cur_frame_pts; } ;
struct TYPE_9__ {scalar_t__* codec_ids; int (* parser_parse ) (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int AV_PARSER_PTS_NB ; 
 int PARSER_FLAG_FETCHED_OFFSET ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  ff_fetch_timestamp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/  const*,int) ; 

int av_parser_parse2(AVCodecParserContext *s, AVCodecContext *avctx,
                     uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size,
                     int64_t pts, int64_t dts, int64_t pos)
{
    int index, i;
    uint8_t dummy_buf[AV_INPUT_BUFFER_PADDING_SIZE];

    av_assert1(avctx->codec_id != AV_CODEC_ID_NONE);

    /* Parsers only work for the specified codec ids. */
    av_assert1(avctx->codec_id == s->parser->codec_ids[0] ||
               avctx->codec_id == s->parser->codec_ids[1] ||
               avctx->codec_id == s->parser->codec_ids[2] ||
               avctx->codec_id == s->parser->codec_ids[3] ||
               avctx->codec_id == s->parser->codec_ids[4]);

    if (!(s->flags & PARSER_FLAG_FETCHED_OFFSET)) {
        s->next_frame_offset =
        s->cur_offset        = pos;
        s->flags            |= PARSER_FLAG_FETCHED_OFFSET;
    }

    if (buf_size == 0) {
        /* padding is always necessary even if EOF, so we add it here */
        memset(dummy_buf, 0, sizeof(dummy_buf));
        buf = dummy_buf;
    } else if (s->cur_offset + buf_size != s->cur_frame_end[s->cur_frame_start_index]) { /* skip remainder packets */
        /* add a new packet descriptor */
        i = (s->cur_frame_start_index + 1) & (AV_PARSER_PTS_NB - 1);
        s->cur_frame_start_index = i;
        s->cur_frame_offset[i]   = s->cur_offset;
        s->cur_frame_end[i]      = s->cur_offset + buf_size;
        s->cur_frame_pts[i]      = pts;
        s->cur_frame_dts[i]      = dts;
        s->cur_frame_pos[i]      = pos;
    }

    if (s->fetch_timestamp) {
        s->fetch_timestamp = 0;
        s->last_pts        = s->pts;
        s->last_dts        = s->dts;
        s->last_pos        = s->pos;
        ff_fetch_timestamp(s, 0, 0, 0);
    }
    /* WARNING: the returned index can be negative */
    index = s->parser->parser_parse(s, avctx, (const uint8_t **) poutbuf,
                                    poutbuf_size, buf, buf_size);
    av_assert0(index > -0x20000000); // The API does not allow returning AVERROR codes
#define FILL(name) if(s->name > 0 && avctx->name <= 0) avctx->name = s->name
    if (avctx->codec_type == AVMEDIA_TYPE_VIDEO) {
        FILL(field_order);
    }

    /* update the file pointer */
    if (*poutbuf_size) {
        /* fill the data for the current frame */
        s->frame_offset = s->next_frame_offset;

        /* offset of the next frame */
        s->next_frame_offset = s->cur_offset + index;
        s->fetch_timestamp   = 1;
    }
    if (index < 0)
        index = 0;
    s->cur_offset += index;
    return index;
}