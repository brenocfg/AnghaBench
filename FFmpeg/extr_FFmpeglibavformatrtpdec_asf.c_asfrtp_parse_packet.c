#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_31__ {int nb_streams; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_30__ {int pos; scalar_t__ eof_reached; } ;
struct TYPE_29__ {size_t stream_index; } ;
struct TYPE_28__ {int /*<<< orphan*/  buf; TYPE_6__* pktbuf; TYPE_6__ pb; } ;
struct TYPE_27__ {int asf_pb_pos; TYPE_11__* asf_ctx; } ;
struct TYPE_26__ {scalar_t__ id; } ;
struct TYPE_25__ {scalar_t__ id; } ;
struct TYPE_24__ {TYPE_2__** streams; TYPE_6__* pb; } ;
typedef  TYPE_3__ RTSPState ;
typedef  TYPE_4__ PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ FFMIN (int,int) ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int av_reallocp (int /*<<< orphan*/ *,int) ; 
 int avio_close_dyn_buf (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int avio_open_dyn_buf (TYPE_6__**) ; 
 int avio_r8 (TYPE_6__*) ; 
 int avio_rb24 (TYPE_6__*) ; 
 int /*<<< orphan*/  avio_skip (TYPE_6__*,int) ; 
 int avio_tell (TYPE_6__*) ; 
 int /*<<< orphan*/  avio_write (TYPE_6__*,int /*<<< orphan*/  const*,int) ; 
 int ff_read_packet (TYPE_11__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (TYPE_6__**) ; 
 int /*<<< orphan*/  ffio_init_context (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_packetizer (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int asfrtp_parse_packet(AVFormatContext *s, PayloadContext *asf,
                               AVStream *st, AVPacket *pkt,
                               uint32_t *timestamp,
                               const uint8_t *buf, int len, uint16_t seq,
                               int flags)
{
    AVIOContext *pb = &asf->pb;
    int res, mflags, len_off;
    RTSPState *rt = s->priv_data;

    if (!rt->asf_ctx)
        return -1;

    if (len > 0) {
        int off, out_len = 0;

        if (len < 4)
            return -1;

        av_freep(&asf->buf);

        ffio_init_context(pb, (uint8_t *)buf, len, 0, NULL, NULL, NULL, NULL);

        while (avio_tell(pb) + 4 < len) {
            int start_off = avio_tell(pb);

            mflags = avio_r8(pb);
            len_off = avio_rb24(pb);
            if (mflags & 0x20)   /**< relative timestamp */
                avio_skip(pb, 4);
            if (mflags & 0x10)   /**< has duration */
                avio_skip(pb, 4);
            if (mflags & 0x8)    /**< has location ID */
                avio_skip(pb, 4);
            off = avio_tell(pb);

            if (!(mflags & 0x40)) {
                /**
                 * If 0x40 is not set, the len_off field specifies an offset
                 * of this packet's payload data in the complete (reassembled)
                 * ASF packet. This is used to spread one ASF packet over
                 * multiple RTP packets.
                 */
                if (asf->pktbuf && len_off != avio_tell(asf->pktbuf)) {
                    ffio_free_dyn_buf(&asf->pktbuf);
                }
                if (!len_off && !asf->pktbuf &&
                    (res = avio_open_dyn_buf(&asf->pktbuf)) < 0)
                    return res;
                if (!asf->pktbuf)
                    return AVERROR(EIO);

                avio_write(asf->pktbuf, buf + off, len - off);
                avio_skip(pb, len - off);
                if (!(flags & RTP_FLAG_MARKER))
                    return -1;
                out_len     = avio_close_dyn_buf(asf->pktbuf, &asf->buf);
                asf->pktbuf = NULL;
            } else {
                /**
                 * If 0x40 is set, the len_off field specifies the length of
                 * the next ASF packet that can be read from this payload
                 * data alone. This is commonly the same as the payload size,
                 * but could be less in case of packet splitting (i.e.
                 * multiple ASF packets in one RTP packet).
                 */

                int cur_len = start_off + len_off - off;
                int prev_len = out_len;
                out_len += cur_len;
                if (FFMIN(cur_len, len - off) < 0)
                    return -1;
                if ((res = av_reallocp(&asf->buf, out_len)) < 0)
                    return res;
                memcpy(asf->buf + prev_len, buf + off,
                       FFMIN(cur_len, len - off));
                avio_skip(pb, cur_len);
            }
        }

        init_packetizer(pb, asf->buf, out_len);
        pb->pos += rt->asf_pb_pos;
        pb->eof_reached = 0;
        rt->asf_ctx->pb = pb;
    }

    for (;;) {
        int i;

        res = ff_read_packet(rt->asf_ctx, pkt);
        rt->asf_pb_pos = avio_tell(pb);
        if (res != 0)
            break;
        for (i = 0; i < s->nb_streams; i++) {
            if (s->streams[i]->id == rt->asf_ctx->streams[pkt->stream_index]->id) {
                pkt->stream_index = i;
                return 1; // FIXME: return 0 if last packet
            }
        }
        av_packet_unref(pkt);
    }

    return res == 1 ? -1 : res;
}