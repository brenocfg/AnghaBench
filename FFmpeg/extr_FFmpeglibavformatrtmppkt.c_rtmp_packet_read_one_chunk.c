#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  enum RTMPPacketType { ____Placeholder_RTMPPacketType } RTMPPacketType ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_7__ {int size; int type; int extra; int ts_field; int timestamp; int read; int offset; int* data; int channel_id; } ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB24 (int*) ; 
 int AV_RB32 (int*) ; 
 int AV_RL16 (int*) ; 
 int AV_RL32 (int*) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int FFMIN (int,int) ; 
 int RTMP_PS_FOURBYTES ; 
 int RTMP_PS_ONEBYTE ; 
 int RTMP_PS_TWELVEBYTES ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int ff_rtmp_check_alloc_array (TYPE_1__**,int*,int) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_1__*) ; 
 int ffurl_read_complete (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int rtmp_packet_read_one_chunk(URLContext *h, RTMPPacket *p,
                                      int chunk_size, RTMPPacket **prev_pkt_ptr,
                                      int *nb_prev_pkt, uint8_t hdr)
{

    uint8_t buf[16];
    int channel_id, timestamp, size;
    uint32_t ts_field; // non-extended timestamp or delta field
    uint32_t extra = 0;
    enum RTMPPacketType type;
    int written = 0;
    int ret, toread;
    RTMPPacket *prev_pkt;

    written++;
    channel_id = hdr & 0x3F;

    if (channel_id < 2) { //special case for channel number >= 64
        buf[1] = 0;
        if (ffurl_read_complete(h, buf, channel_id + 1) != channel_id + 1)
            return AVERROR(EIO);
        written += channel_id + 1;
        channel_id = AV_RL16(buf) + 64;
    }
    if ((ret = ff_rtmp_check_alloc_array(prev_pkt_ptr, nb_prev_pkt,
                                         channel_id)) < 0)
        return ret;
    prev_pkt = *prev_pkt_ptr;
    size  = prev_pkt[channel_id].size;
    type  = prev_pkt[channel_id].type;
    extra = prev_pkt[channel_id].extra;

    hdr >>= 6; // header size indicator
    if (hdr == RTMP_PS_ONEBYTE) {
        ts_field = prev_pkt[channel_id].ts_field;
    } else {
        if (ffurl_read_complete(h, buf, 3) != 3)
            return AVERROR(EIO);
        written += 3;
        ts_field = AV_RB24(buf);
        if (hdr != RTMP_PS_FOURBYTES) {
            if (ffurl_read_complete(h, buf, 3) != 3)
                return AVERROR(EIO);
            written += 3;
            size = AV_RB24(buf);
            if (ffurl_read_complete(h, buf, 1) != 1)
                return AVERROR(EIO);
            written++;
            type = buf[0];
            if (hdr == RTMP_PS_TWELVEBYTES) {
                if (ffurl_read_complete(h, buf, 4) != 4)
                    return AVERROR(EIO);
                written += 4;
                extra = AV_RL32(buf);
            }
        }
    }
    if (ts_field == 0xFFFFFF) {
        if (ffurl_read_complete(h, buf, 4) != 4)
            return AVERROR(EIO);
        timestamp = AV_RB32(buf);
    } else {
        timestamp = ts_field;
    }
    if (hdr != RTMP_PS_TWELVEBYTES)
        timestamp += prev_pkt[channel_id].timestamp;

    if (prev_pkt[channel_id].read && size != prev_pkt[channel_id].size) {
        av_log(h, AV_LOG_ERROR, "RTMP packet size mismatch %d != %d\n",
                                size, prev_pkt[channel_id].size);
        ff_rtmp_packet_destroy(&prev_pkt[channel_id]);
        prev_pkt[channel_id].read = 0;
        return AVERROR_INVALIDDATA;
    }

    if (!prev_pkt[channel_id].read) {
        if ((ret = ff_rtmp_packet_create(p, channel_id, type, timestamp,
                                         size)) < 0)
            return ret;
        p->read = written;
        p->offset = 0;
        prev_pkt[channel_id].ts_field   = ts_field;
        prev_pkt[channel_id].timestamp  = timestamp;
    } else {
        // previous packet in this channel hasn't completed reading
        RTMPPacket *prev = &prev_pkt[channel_id];
        p->data          = prev->data;
        p->size          = prev->size;
        p->channel_id    = prev->channel_id;
        p->type          = prev->type;
        p->ts_field      = prev->ts_field;
        p->extra         = prev->extra;
        p->offset        = prev->offset;
        p->read          = prev->read + written;
        p->timestamp     = prev->timestamp;
        prev->data       = NULL;
    }
    p->extra = extra;
    // save history
    prev_pkt[channel_id].channel_id = channel_id;
    prev_pkt[channel_id].type       = type;
    prev_pkt[channel_id].size       = size;
    prev_pkt[channel_id].extra      = extra;
    size = size - p->offset;

    toread = FFMIN(size, chunk_size);
    if (ffurl_read_complete(h, p->data + p->offset, toread) != toread) {
        ff_rtmp_packet_destroy(p);
        return AVERROR(EIO);
    }
    size      -= toread;
    p->read   += toread;
    p->offset += toread;

    if (size > 0) {
       RTMPPacket *prev = &prev_pkt[channel_id];
       prev->data = p->data;
       prev->read = p->read;
       prev->offset = p->offset;
       p->data      = NULL;
       return AVERROR(EAGAIN);
    }

    prev_pkt[channel_id].read = 0; // read complete; reset if needed
    return p->read;
}