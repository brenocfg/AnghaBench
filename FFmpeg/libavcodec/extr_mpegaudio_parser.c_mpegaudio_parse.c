#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_12__ {int codec_id; int sample_rate; int channels; int bit_rate; } ;
struct TYPE_11__ {int duration; int flags; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int state; } ;
struct TYPE_10__ {int frame_size; int header_count; int header; int no_bitrate; TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ MpegAudioParseContext ;
typedef  TYPE_3__ AVCodecParserContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int APE_TAG_FOOTER_BYTES ; 
 char* APE_TAG_PREAMBLE ; 
 int AV_CODEC_ID_MP3ADU ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int END_NOT_FOUND ; 
 int FFMIN (int,int) ; 
 int ID3v1_TAG_SIZE ; 
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 int SAME_HEADER_MASK ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*) ; 
 scalar_t__ ff_combine_frame (TYPE_1__*,int,int const**,int*) ; 
 int ff_mpa_decode_header (int,int*,int*,int*,int*,int*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 

__attribute__((used)) static int mpegaudio_parse(AVCodecParserContext *s1,
                           AVCodecContext *avctx,
                           const uint8_t **poutbuf, int *poutbuf_size,
                           const uint8_t *buf, int buf_size)
{
    MpegAudioParseContext *s = s1->priv_data;
    ParseContext *pc = &s->pc;
    uint32_t state= pc->state;
    int i;
    int next= END_NOT_FOUND;
    int flush = !buf_size;

    for(i=0; i<buf_size; ){
        if(s->frame_size){
            int inc= FFMIN(buf_size - i, s->frame_size);
            i += inc;
            s->frame_size -= inc;
            state = 0;

            if(!s->frame_size){
                next= i;
                break;
            }
        }else{
            while(i<buf_size){
                int ret, sr, channels, bit_rate, frame_size;
                enum AVCodecID codec_id = avctx->codec_id;

                state= (state<<8) + buf[i++];

                ret = ff_mpa_decode_header(state, &sr, &channels, &frame_size, &bit_rate, &codec_id);
                if (ret < 4) {
                    if (i > 4)
                        s->header_count = -2;
                } else {
                    int header_threshold = avctx->codec_id != AV_CODEC_ID_NONE && avctx->codec_id != codec_id;
                    if((state&SAME_HEADER_MASK) != (s->header&SAME_HEADER_MASK) && s->header)
                        s->header_count= -3;
                    s->header= state;
                    s->header_count++;
                    s->frame_size = ret-4;

                    if (s->header_count > header_threshold) {
                        avctx->sample_rate= sr;
                        avctx->channels   = channels;
                        s1->duration      = frame_size;
                        avctx->codec_id   = codec_id;
                        if (s->no_bitrate || !avctx->bit_rate) {
                            s->no_bitrate = 1;
                            avctx->bit_rate += (bit_rate - avctx->bit_rate) / (s->header_count - header_threshold);
                        }
                    }

                    if (s1->flags & PARSER_FLAG_COMPLETE_FRAMES) {
                        s->frame_size = 0;
                        next = buf_size;
                    } else if (codec_id == AV_CODEC_ID_MP3ADU) {
                        avpriv_report_missing_feature(avctx,
                            "MP3ADU full parser");
                        *poutbuf = NULL;
                        *poutbuf_size = 0;
                        return buf_size; /* parsers must not return error codes */
                    }

                    break;
                }
            }
        }
    }

    pc->state= state;
    if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
        *poutbuf = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    if (flush && buf_size >= ID3v1_TAG_SIZE && memcmp(buf, "TAG", 3) == 0) {
        *poutbuf = NULL;
        *poutbuf_size = 0;
        return next;
    }

    if (flush && buf_size >= APE_TAG_FOOTER_BYTES && memcmp(buf, APE_TAG_PREAMBLE, 8) == 0) {
        *poutbuf = NULL;
        *poutbuf_size = 0;
        return next;
    }

    *poutbuf = buf;
    *poutbuf_size = buf_size;
    return next;
}