#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_16__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_15__ {int size; int* data; } ;
struct TYPE_14__ {int have_end; scalar_t__ loop; TYPE_2__* prev_pkt; int /*<<< orphan*/  last_pos; } ;
typedef  TYPE_1__ GIFContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int GIF_APP_EXT_LABEL ; 
 int GIF_EXTENSION_INTRODUCER ; 
 int GIF_TRAILER ; 
 TYPE_2__* av_packet_alloc () ; 
 int av_packet_ref (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gif_get_delay (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int gif_parse_packet (TYPE_3__*,int*,int) ; 

__attribute__((used)) static int gif_write_packet(AVFormatContext *s, AVPacket *new_pkt)
{
    GIFContext *gif = s->priv_data;
    AVIOContext *pb = s->pb;
    AVPacket *pkt = gif->prev_pkt;

    if (!gif->prev_pkt) {
        gif->prev_pkt = av_packet_alloc();
        if (!gif->prev_pkt)
            return AVERROR(ENOMEM);
        return av_packet_ref(gif->prev_pkt, new_pkt);
    }

    gif->last_pos = avio_tell(pb);
    if (pkt->size > 0)
        gif->have_end = pkt->data[pkt->size - 1] == GIF_TRAILER;

    if (!gif->last_pos) {
        int delay_pos;
        int off = 13;

        if (pkt->size < 13)
            return AVERROR(EINVAL);

        if (pkt->data[10] & 0x80)
            off += 3 * (1 << ((pkt->data[10] & 0x07) + 1));

        if (pkt->size < off + 2)
            return AVERROR(EINVAL);

        avio_write(pb, pkt->data, off);

        if (pkt->data[off] == GIF_EXTENSION_INTRODUCER && pkt->data[off + 1] == 0xff)
            off += 19;

        if (pkt->size <= off)
            return AVERROR(EINVAL);

        /* "NETSCAPE EXTENSION" for looped animation GIF */
        if (gif->loop >= 0) {
            avio_w8(pb, GIF_EXTENSION_INTRODUCER); /* GIF Extension code */
            avio_w8(pb, GIF_APP_EXT_LABEL); /* Application Extension Label */
            avio_w8(pb, 0x0b); /* Length of Application Block */
            avio_write(pb, "NETSCAPE2.0", sizeof("NETSCAPE2.0") - 1);
            avio_w8(pb, 0x03); /* Length of Data Sub-Block */
            avio_w8(pb, 0x01);
            avio_wl16(pb, (uint16_t)gif->loop);
            avio_w8(pb, 0x00); /* Data Sub-block Terminator */
        }

        delay_pos = gif_parse_packet(s, pkt->data + off, pkt->size - off);
        if (delay_pos > 0 && delay_pos < pkt->size - off - 2) {
            avio_write(pb, pkt->data + off, delay_pos);
            avio_wl16(pb, gif_get_delay(gif, pkt, new_pkt));
            avio_write(pb, pkt->data + off + delay_pos + 2, pkt->size - off - delay_pos - 2);
        } else {
            avio_write(pb, pkt->data + off, pkt->size - off);
        }
    } else {
        int delay_pos = gif_parse_packet(s, pkt->data, pkt->size);

        if (delay_pos > 0 && delay_pos < pkt->size - 2) {
            avio_write(pb, pkt->data, delay_pos);
            avio_wl16(pb, gif_get_delay(gif, pkt, new_pkt));
            avio_write(pb, pkt->data + delay_pos + 2, pkt->size - delay_pos - 2);
        } else {
            avio_write(pb, pkt->data, pkt->size);
        }
    }

    av_packet_unref(gif->prev_pkt);
    if (new_pkt)
        return av_packet_ref(gif->prev_pkt, new_pkt);

    return 0;
}