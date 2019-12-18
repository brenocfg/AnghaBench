#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_5__ {size_t channel_id; scalar_t__ extra; scalar_t__ timestamp; int ts_field; int type; int size; int* data; } ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32 (int*,int) ; 
 int FFMIN (int,int) ; 
 int RTMP_PS_EIGHTBYTES ; 
 int RTMP_PS_FOURBYTES ; 
 int RTMP_PS_ONEBYTE ; 
 int RTMP_PS_TWELVEBYTES ; 
 int /*<<< orphan*/  bytestream_put_be24 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_le16 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int**,scalar_t__) ; 
 int ff_rtmp_check_alloc_array (TYPE_1__**,int*,size_t) ; 
 int ffurl_write (int /*<<< orphan*/ *,int*,int) ; 

int ff_rtmp_packet_write(URLContext *h, RTMPPacket *pkt,
                         int chunk_size, RTMPPacket **prev_pkt_ptr,
                         int *nb_prev_pkt)
{
    uint8_t pkt_hdr[16], *p = pkt_hdr;
    int mode = RTMP_PS_TWELVEBYTES;
    int off = 0;
    int written = 0;
    int ret;
    RTMPPacket *prev_pkt;
    int use_delta; // flag if using timestamp delta, not RTMP_PS_TWELVEBYTES
    uint32_t timestamp; // full 32-bit timestamp or delta value

    if ((ret = ff_rtmp_check_alloc_array(prev_pkt_ptr, nb_prev_pkt,
                                         pkt->channel_id)) < 0)
        return ret;
    prev_pkt = *prev_pkt_ptr;

    //if channel_id = 0, this is first presentation of prev_pkt, send full hdr.
    use_delta = prev_pkt[pkt->channel_id].channel_id &&
        pkt->extra == prev_pkt[pkt->channel_id].extra &&
        pkt->timestamp >= prev_pkt[pkt->channel_id].timestamp;

    timestamp = pkt->timestamp;
    if (use_delta) {
        timestamp -= prev_pkt[pkt->channel_id].timestamp;
    }
    if (timestamp >= 0xFFFFFF) {
        pkt->ts_field = 0xFFFFFF;
    } else {
        pkt->ts_field = timestamp;
    }

    if (use_delta) {
        if (pkt->type == prev_pkt[pkt->channel_id].type &&
            pkt->size == prev_pkt[pkt->channel_id].size) {
            mode = RTMP_PS_FOURBYTES;
            if (pkt->ts_field == prev_pkt[pkt->channel_id].ts_field)
                mode = RTMP_PS_ONEBYTE;
        } else {
            mode = RTMP_PS_EIGHTBYTES;
        }
    }

    if (pkt->channel_id < 64) {
        bytestream_put_byte(&p, pkt->channel_id | (mode << 6));
    } else if (pkt->channel_id < 64 + 256) {
        bytestream_put_byte(&p, 0               | (mode << 6));
        bytestream_put_byte(&p, pkt->channel_id - 64);
    } else {
        bytestream_put_byte(&p, 1               | (mode << 6));
        bytestream_put_le16(&p, pkt->channel_id - 64);
    }
    if (mode != RTMP_PS_ONEBYTE) {
        bytestream_put_be24(&p, pkt->ts_field);
        if (mode != RTMP_PS_FOURBYTES) {
            bytestream_put_be24(&p, pkt->size);
            bytestream_put_byte(&p, pkt->type);
            if (mode == RTMP_PS_TWELVEBYTES)
                bytestream_put_le32(&p, pkt->extra);
        }
    }
    if (pkt->ts_field == 0xFFFFFF)
        bytestream_put_be32(&p, timestamp);
    // save history
    prev_pkt[pkt->channel_id].channel_id = pkt->channel_id;
    prev_pkt[pkt->channel_id].type       = pkt->type;
    prev_pkt[pkt->channel_id].size       = pkt->size;
    prev_pkt[pkt->channel_id].timestamp  = pkt->timestamp;
    prev_pkt[pkt->channel_id].ts_field   = pkt->ts_field;
    prev_pkt[pkt->channel_id].extra      = pkt->extra;

    if ((ret = ffurl_write(h, pkt_hdr, p - pkt_hdr)) < 0)
        return ret;
    written = p - pkt_hdr + pkt->size;
    while (off < pkt->size) {
        int towrite = FFMIN(chunk_size, pkt->size - off);
        if ((ret = ffurl_write(h, pkt->data + off, towrite)) < 0)
            return ret;
        off += towrite;
        if (off < pkt->size) {
            uint8_t marker = 0xC0 | pkt->channel_id;
            if ((ret = ffurl_write(h, &marker, 1)) < 0)
                return ret;
            written++;
            if (pkt->ts_field == 0xFFFFFF) {
                uint8_t ts_header[4];
                AV_WB32(ts_header, timestamp);
                if ((ret = ffurl_write(h, ts_header, 4)) < 0)
                    return ret;
                written += 4;
            }
        }
    }
    return written;
}