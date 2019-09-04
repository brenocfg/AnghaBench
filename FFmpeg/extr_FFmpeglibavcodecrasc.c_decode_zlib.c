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
struct TYPE_12__ {int /*<<< orphan*/  avail_out; scalar_t__ next_out; int /*<<< orphan*/  avail_in; scalar_t__ next_in; } ;
struct TYPE_11__ {TYPE_1__* priv_data; } ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {TYPE_4__ zstream; int /*<<< orphan*/  delta_size; scalar_t__ delta; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  av_fast_padded_malloc (scalar_t__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_tell (int /*<<< orphan*/ *) ; 
 int inflate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int inflateReset (TYPE_4__*) ; 

__attribute__((used)) static int decode_zlib(AVCodecContext *avctx, AVPacket *avpkt,
                       unsigned size, unsigned uncompressed_size)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int zret;

    zret = inflateReset(&s->zstream);
    if (zret != Z_OK) {
        av_log(avctx, AV_LOG_ERROR, "Inflate reset error: %d\n", zret);
        return AVERROR_EXTERNAL;
    }

    av_fast_padded_malloc(&s->delta, &s->delta_size, uncompressed_size);
    if (!s->delta)
        return AVERROR(ENOMEM);

    s->zstream.next_in  = avpkt->data + bytestream2_tell(gb);
    s->zstream.avail_in = FFMIN(size, bytestream2_get_bytes_left(gb));

    s->zstream.next_out  = s->delta;
    s->zstream.avail_out = s->delta_size;

    zret = inflate(&s->zstream, Z_FINISH);
    if (zret != Z_STREAM_END) {
        av_log(avctx, AV_LOG_ERROR,
               "Inflate failed with return code: %d.\n", zret);
        return AVERROR_INVALIDDATA;
    }

    return 0;
}