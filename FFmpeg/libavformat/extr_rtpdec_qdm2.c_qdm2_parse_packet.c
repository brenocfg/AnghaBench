#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_14__ {TYPE_1__* codecpar; } ;
struct TYPE_13__ {scalar_t__ n_pkts; scalar_t__* len; scalar_t__ subpkts_per_block; scalar_t__ cache; int /*<<< orphan*/  timestamp; } ;
struct TYPE_12__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ PayloadContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 scalar_t__ AV_CODEC_ID_QDM2 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  RTP_NOTS_VALUE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int qdm2_parse_config (TYPE_2__*,TYPE_3__*,int const*,int const*) ; 
 int qdm2_parse_subpacket (TYPE_2__*,TYPE_3__*,int const*,int const*) ; 
 int qdm2_restore_block (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qdm2_parse_packet(AVFormatContext *s, PayloadContext *qdm,
                             AVStream *st, AVPacket *pkt,
                             uint32_t *timestamp,
                             const uint8_t *buf, int len, uint16_t seq,
                             int flags)
{
    int res = AVERROR_INVALIDDATA, n;
    const uint8_t *end = buf + len, *p = buf;

    if (len > 0) {
        if (len < 2)
            return AVERROR_INVALIDDATA;

        /* configuration block */
        if (*p == 0xff) {
            if (qdm->n_pkts > 0) {
                av_log(s, AV_LOG_WARNING,
                       "Out of sequence config - dropping queue\n");
                qdm->n_pkts = 0;
                memset(qdm->len, 0, sizeof(qdm->len));
            }

            if ((res = qdm2_parse_config(qdm, st, ++p, end)) < 0)
                return res;
            p += res;

            /* We set codec_id to AV_CODEC_ID_NONE initially to
             * delay decoder initialization since extradata is
             * carried within the RTP stream, not SDP. Here,
             * by setting codec_id to AV_CODEC_ID_QDM2, we are signalling
             * to the decoder that it is OK to initialize. */
            st->codecpar->codec_id = AV_CODEC_ID_QDM2;
        }
        if (st->codecpar->codec_id == AV_CODEC_ID_NONE)
            return AVERROR(EAGAIN);

        /* subpackets */
        while (end - p >= 4) {
            if ((res = qdm2_parse_subpacket(qdm, st, p, end)) < 0)
                return res;
            p += res;
        }

        qdm->timestamp = *timestamp;
        if (++qdm->n_pkts < qdm->subpkts_per_block)
            return AVERROR(EAGAIN);
        qdm->cache = 0;
        for (n = 0; n < 0x80; n++)
            if (qdm->len[n] > 0)
                qdm->cache++;
    }

    /* output the subpackets into freshly created superblock structures */
    if (!qdm->cache || (res = qdm2_restore_block(qdm, st, pkt)) < 0)
        return res;
    if (--qdm->cache == 0)
        qdm->n_pkts = 0;

    *timestamp = qdm->timestamp;
    qdm->timestamp = RTP_NOTS_VALUE;

    return (qdm->cache > 0) ? 1 : 0;
}