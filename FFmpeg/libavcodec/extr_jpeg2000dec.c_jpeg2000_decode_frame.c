#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_19__ {void* f; } ;
typedef  TYPE_2__ ThreadFrame ;
struct TYPE_18__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_23__ {scalar_t__ pix_fmt; TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  (* execute2 ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int) ;TYPE_3__* priv_data; } ;
struct TYPE_22__ {int key_frame; int /*<<< orphan*/ * data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_21__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int curtileno; int numXtiles; int numYtiles; int /*<<< orphan*/  g; TYPE_1__ sar; int /*<<< orphan*/  palette; TYPE_6__* avctx; int /*<<< orphan*/  cdef; } ;
typedef  TYPE_3__ Jpeg2000DecoderContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int JP2_SIG_TYPE ; 
 int JP2_SIG_VALUE ; 
 scalar_t__ JPEG2000_SOC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bytestream2_get_be16u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be32u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bytestream2_peek_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_thread_get_buffer (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jp2_find_codestream (TYPE_3__*) ; 
 int /*<<< orphan*/  jpeg2000_dec_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  jpeg2000_decode_tile ; 
 int jpeg2000_read_bitstream_packets (TYPE_3__*) ; 
 int jpeg2000_read_main_headers (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int jpeg2000_decode_frame(AVCodecContext *avctx, void *data,
                                 int *got_frame, AVPacket *avpkt)
{
    Jpeg2000DecoderContext *s = avctx->priv_data;
    ThreadFrame frame = { .f = data };
    AVFrame *picture = data;
    int ret;

    s->avctx     = avctx;
    bytestream2_init(&s->g, avpkt->data, avpkt->size);
    s->curtileno = -1;
    memset(s->cdef, -1, sizeof(s->cdef));

    if (bytestream2_get_bytes_left(&s->g) < 2) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }

    // check if the image is in jp2 format
    if (bytestream2_get_bytes_left(&s->g) >= 12 &&
       (bytestream2_get_be32u(&s->g) == 12) &&
       (bytestream2_get_be32u(&s->g) == JP2_SIG_TYPE) &&
       (bytestream2_get_be32u(&s->g) == JP2_SIG_VALUE)) {
        if (!jp2_find_codestream(s)) {
            av_log(avctx, AV_LOG_ERROR,
                   "Could not find Jpeg2000 codestream atom.\n");
            ret = AVERROR_INVALIDDATA;
            goto end;
        }
    } else {
        bytestream2_seek(&s->g, 0, SEEK_SET);
    }

    while (bytestream2_get_bytes_left(&s->g) >= 3 && bytestream2_peek_be16(&s->g) != JPEG2000_SOC)
        bytestream2_skip(&s->g, 1);

    if (bytestream2_get_be16u(&s->g) != JPEG2000_SOC) {
        av_log(avctx, AV_LOG_ERROR, "SOC marker not present\n");
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    if (ret = jpeg2000_read_main_headers(s))
        goto end;

    /* get picture buffer */
    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        goto end;
    picture->pict_type = AV_PICTURE_TYPE_I;
    picture->key_frame = 1;

    if (ret = jpeg2000_read_bitstream_packets(s))
        goto end;

    avctx->execute2(avctx, jpeg2000_decode_tile, picture, NULL, s->numXtiles * s->numYtiles);

    jpeg2000_dec_cleanup(s);

    *got_frame = 1;

    if (s->avctx->pix_fmt == AV_PIX_FMT_PAL8)
        memcpy(picture->data[1], s->palette, 256 * sizeof(uint32_t));
    if (s->sar.num && s->sar.den)
        avctx->sample_aspect_ratio = s->sar;
    s->sar.num = s->sar.den = 0;

    return bytestream2_tell(&s->g);

end:
    jpeg2000_dec_cleanup(s);
    return ret;
}