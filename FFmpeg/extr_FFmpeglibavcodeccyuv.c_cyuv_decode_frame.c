#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
struct TYPE_13__ {scalar_t__ codec_id; int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_12__ {unsigned char** data; int* linesize; } ;
struct TYPE_11__ {unsigned char* data; int size; } ;
struct TYPE_10__ {int height; int width; } ;
typedef  TYPE_1__ CyuvDecodeContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_AURA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_UYVY422 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV411P ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int cyuv_decode_frame(AVCodecContext *avctx,
                             void *data, int *got_frame,
                             AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    CyuvDecodeContext *s=avctx->priv_data;
    AVFrame *frame = data;

    unsigned char *y_plane;
    unsigned char *u_plane;
    unsigned char *v_plane;
    int y_ptr;
    int u_ptr;
    int v_ptr;

    /* prediction error tables (make it clear that they are signed values) */
    const signed char *y_table = (const signed char*)buf +  0;
    const signed char *u_table = (const signed char*)buf + 16;
    const signed char *v_table = (const signed char*)buf + 32;

    unsigned char y_pred, u_pred, v_pred;
    int stream_ptr;
    unsigned char cur_byte;
    int pixel_groups;
    int rawsize = s->height * FFALIGN(s->width,2) * 2;
    int ret;

    if (avctx->codec_id == AV_CODEC_ID_AURA) {
        y_table = u_table;
        u_table = v_table;
    }
    /* sanity check the buffer size: A buffer has 3x16-bytes tables
     * followed by (height) lines each with 3 bytes to represent groups
     * of 4 pixels. Thus, the total size of the buffer ought to be:
     *    (3 * 16) + height * (width * 3 / 4) */
    if (buf_size == 48 + s->height * (s->width * 3 / 4)) {
        avctx->pix_fmt = AV_PIX_FMT_YUV411P;
    } else if(buf_size == rawsize ) {
        avctx->pix_fmt = AV_PIX_FMT_UYVY422;
    } else {
        av_log(avctx, AV_LOG_ERROR, "got a buffer with %d bytes when %d were expected\n",
               buf_size, 48 + s->height * (s->width * 3 / 4));
        return AVERROR_INVALIDDATA;
    }

    /* pixel data starts 48 bytes in, after 3x16-byte tables */
    stream_ptr = 48;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    y_plane = frame->data[0];
    u_plane = frame->data[1];
    v_plane = frame->data[2];

    if (buf_size == rawsize) {
        int linesize = FFALIGN(s->width,2) * 2;
        y_plane += frame->linesize[0] * s->height;
        for (stream_ptr = 0; stream_ptr < rawsize; stream_ptr += linesize) {
            y_plane -= frame->linesize[0];
            memcpy(y_plane, buf+stream_ptr, linesize);
        }
    } else {

    /* iterate through each line in the height */
    for (y_ptr = 0, u_ptr = 0, v_ptr = 0;
         y_ptr < (s->height * frame->linesize[0]);
         y_ptr += frame->linesize[0] - s->width,
         u_ptr += frame->linesize[1] - s->width / 4,
         v_ptr += frame->linesize[2] - s->width / 4) {

        /* reset predictors */
        cur_byte = buf[stream_ptr++];
        u_plane[u_ptr++] = u_pred = cur_byte & 0xF0;
        y_plane[y_ptr++] = y_pred = (cur_byte & 0x0F) << 4;

        cur_byte = buf[stream_ptr++];
        v_plane[v_ptr++] = v_pred = cur_byte & 0xF0;
        y_pred += y_table[cur_byte & 0x0F];
        y_plane[y_ptr++] = y_pred;

        cur_byte = buf[stream_ptr++];
        y_pred += y_table[cur_byte & 0x0F];
        y_plane[y_ptr++] = y_pred;
        y_pred += y_table[(cur_byte & 0xF0) >> 4];
        y_plane[y_ptr++] = y_pred;

        /* iterate through the remaining pixel groups (4 pixels/group) */
        pixel_groups = s->width / 4 - 1;
        while (pixel_groups--) {

            cur_byte = buf[stream_ptr++];
            u_pred += u_table[(cur_byte & 0xF0) >> 4];
            u_plane[u_ptr++] = u_pred;
            y_pred += y_table[cur_byte & 0x0F];
            y_plane[y_ptr++] = y_pred;

            cur_byte = buf[stream_ptr++];
            v_pred += v_table[(cur_byte & 0xF0) >> 4];
            v_plane[v_ptr++] = v_pred;
            y_pred += y_table[cur_byte & 0x0F];
            y_plane[y_ptr++] = y_pred;

            cur_byte = buf[stream_ptr++];
            y_pred += y_table[cur_byte & 0x0F];
            y_plane[y_ptr++] = y_pred;
            y_pred += y_table[(cur_byte & 0xF0) >> 4];
            y_plane[y_ptr++] = y_pred;

        }
    }
    }

    *got_frame = 1;

    return buf_size;
}