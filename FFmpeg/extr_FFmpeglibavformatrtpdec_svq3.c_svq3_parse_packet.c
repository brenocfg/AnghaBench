#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  codec_id; scalar_t__ extradata; scalar_t__ extradata_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; TYPE_5__* codecpar; } ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  pktbuf; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_SVQ3 ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__,int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int const*,int) ; 
 scalar_t__ ff_alloc_extradata (TYPE_5__*,int) ; 
 int ff_rtp_finalize_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,...) ; 

__attribute__((used)) static int svq3_parse_packet (AVFormatContext *s, PayloadContext *sv,
                              AVStream *st, AVPacket *pkt,
                              uint32_t *timestamp,
                              const uint8_t *buf, int len, uint16_t seq,
                              int flags)
{
    int config_packet, start_packet, end_packet;

    if (len < 2)
        return AVERROR_INVALIDDATA;

    config_packet = buf[0] & 0x40;
    start_packet  = buf[0] & 0x20;
    end_packet    = buf[0] & 0x10;
    buf += 2;     // ignore buf[1]
    len -= 2;

    if (config_packet) {

        av_freep(&st->codecpar->extradata);
        st->codecpar->extradata_size = 0;

        if (len < 2 || ff_alloc_extradata(st->codecpar, len + 8))
            return AVERROR_INVALIDDATA;

        memcpy(st->codecpar->extradata, "SEQH", 4);
        AV_WB32(st->codecpar->extradata + 4, len);
        memcpy(st->codecpar->extradata + 8, buf, len);

        /* We set codec_id to AV_CODEC_ID_NONE initially to
         * delay decoder initialization since extradata is
         * carried within the RTP stream, not SDP. Here,
         * by setting codec_id to AV_CODEC_ID_SVQ3, we are signalling
         * to the decoder that it is OK to initialize. */
        st->codecpar->codec_id = AV_CODEC_ID_SVQ3;

        return AVERROR(EAGAIN);
    }

    if (start_packet) {
        int res;

        ffio_free_dyn_buf(&sv->pktbuf);
        if ((res = avio_open_dyn_buf(&sv->pktbuf)) < 0)
            return res;
        sv->timestamp   = *timestamp;
    }

    if (!sv->pktbuf)
        return AVERROR_INVALIDDATA;

    avio_write(sv->pktbuf, buf, len);

    if (end_packet) {
        int ret = ff_rtp_finalize_packet(pkt, &sv->pktbuf, st->index);
        if (ret < 0)
            return ret;

        *timestamp        = sv->timestamp;
        return 0;
    }

    return AVERROR(EAGAIN);
}