#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hb_stream_t ;
struct TYPE_14__ {int codec_param; int stream_type; void* stream_kind; TYPE_1__* probe_buf; } ;
typedef  TYPE_2__ hb_pes_stream_t ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_15__ {int codec_id; } ;
struct TYPE_13__ {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ AVCodec ;

/* Variables and functions */
#define  AV_CODEC_ID_MPEG1VIDEO 129 
#define  AV_CODEC_ID_MPEG2VIDEO 128 
 void* V ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_parser_init (int /*<<< orphan*/ ) ; 
 int av_parser_parse2 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **,int*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* avcodec_alloc_context3 (TYPE_4__*) ; 
 TYPE_4__* avcodec_find_decoder (int) ; 
 int /*<<< orphan*/  hb_avcodec_free_context (TYPE_3__**) ; 
 scalar_t__ hb_avcodec_open (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 

__attribute__((used)) static int
do_deep_probe(hb_stream_t *stream, hb_pes_stream_t *pes)
{
    int       result = 0;
    AVCodec * codec = avcodec_find_decoder(pes->codec_param);

    if (codec == NULL)
    {
        return -1;
    }

    AVCodecContext       * context = avcodec_alloc_context3(codec);
    AVCodecParserContext * parser  = av_parser_init(codec->id);

    if (context == NULL)
    {
        return -1;
    }
    if (parser == NULL)
    {
        return -1;
    }
    if (hb_avcodec_open(context, codec, NULL, 0))
    {
        return -1;
    }

    int pos = 0;
    while (pos < pes->probe_buf->size)
    {
        int       len, out_size;
        uint8_t * out;

        len = av_parser_parse2(parser, context, &out, &out_size,
                               pes->probe_buf->data + pos,
                               pes->probe_buf->size - pos, 0, 0, 0);
        pos += len;
        if (out_size == 0)
        {
            continue;
        }
        // Parser changes context->codec_id if it detects a different but
        // related stream type.  E.g. AV_CODEC_ID_MPEG2VIDEO gets changed
        // to AV_CODEC_ID_MPEG1VIDEO when the stream is MPEG-1
        switch (context->codec_id)
        {
            case AV_CODEC_ID_MPEG1VIDEO:
                pes->codec_param = context->codec_id;
                pes->stream_type = 0x01;
                pes->stream_kind = V;
                result = 1;
                break;

            case AV_CODEC_ID_MPEG2VIDEO:
                pes->codec_param = context->codec_id;
                pes->stream_type = 0x02;
                pes->stream_kind = V;
                result = 1;
                break;

            default:
                hb_error("do_deep_probe: unexpected codec_id (%d)",
                         context->codec_id);
                result = -1;
                break;
        }
    }
    av_parser_close(parser);
    hb_avcodec_free_context(&context);

    return result;
}