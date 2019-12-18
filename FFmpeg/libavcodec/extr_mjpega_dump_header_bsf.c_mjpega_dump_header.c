#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int size; int* data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
#define  APP1 132 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RB16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_RL32 (char*) ; 
#define  DHT 131 
#define  DQT 130 
#define  SOF0 129 
 int SOI ; 
#define  SOS 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int av_new_packet (TYPE_1__*,int) ; 
 int av_packet_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int**,char*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int**,int) ; 
 int ff_bsf_get_packet (int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static int mjpega_dump_header(AVBSFContext *ctx, AVPacket *out)
{
    AVPacket *in;
    uint8_t *out_buf;
    unsigned dqt = 0, dht = 0, sof0 = 0;
    int ret = 0, i;

    ret = ff_bsf_get_packet(ctx, &in);
    if (ret < 0)
        return ret;

    ret = av_new_packet(out, in->size + 44);
    if (ret < 0)
        goto fail;

    ret = av_packet_copy_props(out, in);
    if (ret < 0)
        goto fail;

    out_buf = out->data;
    bytestream_put_byte(&out_buf, 0xff);
    bytestream_put_byte(&out_buf, SOI);
    bytestream_put_byte(&out_buf, 0xff);
    bytestream_put_byte(&out_buf, APP1);
    bytestream_put_be16(&out_buf, 42); /* size */
    bytestream_put_be32(&out_buf, 0);
    bytestream_put_buffer(&out_buf, "mjpg", 4);
    bytestream_put_be32(&out_buf, in->size + 44); /* field size */
    bytestream_put_be32(&out_buf, in->size + 44); /* pad field size */
    bytestream_put_be32(&out_buf, 0);             /* next ptr */

    for (i = 0; i < in->size - 1; i++) {
        if (in->data[i] == 0xff) {
            switch (in->data[i + 1]) {
            case DQT:  dqt  = i + 46; break;
            case DHT:  dht  = i + 46; break;
            case SOF0: sof0 = i + 46; break;
            case SOS:
                bytestream_put_be32(&out_buf, dqt); /* quant off */
                bytestream_put_be32(&out_buf, dht); /* huff off */
                bytestream_put_be32(&out_buf, sof0); /* image off */
                bytestream_put_be32(&out_buf, i + 46); /* scan off */
                bytestream_put_be32(&out_buf, i + 46 + AV_RB16(in->data + i + 2)); /* data off */
                bytestream_put_buffer(&out_buf, in->data + 2, in->size - 2); /* skip already written SOI */

                out->size = out_buf - out->data;
                av_packet_free(&in);
                return 0;
            case APP1:
                if (i + 8 < in->size && AV_RL32(in->data + i + 8) == AV_RL32("mjpg")) {
                    av_log(ctx, AV_LOG_ERROR, "bitstream already formatted\n");
                    av_packet_unref(out);
                    av_packet_move_ref(out, in);
                    av_packet_free(&in);
                    return 0;
                }
            }
        }
    }
    av_log(ctx, AV_LOG_ERROR, "could not find SOS marker in bitstream\n");
fail:
    av_packet_unref(out);
    av_packet_free(&in);
    return AVERROR_INVALIDDATA;
}