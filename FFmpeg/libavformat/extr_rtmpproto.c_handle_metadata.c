#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int flv_size; int flv_off; int /*<<< orphan*/  const* flv_data; } ;
struct TYPE_7__ {int size; int timestamp; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int RTMP_HEADER ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int av_reallocp (int /*<<< orphan*/  const**,int) ; 
 int bytestream_get_be24 (int /*<<< orphan*/  const**) ; 
 int bytestream_get_byte (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  bytestream_put_be24 (int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int update_offset (TYPE_2__*,int) ; 

__attribute__((used)) static int handle_metadata(RTMPContext *rt, RTMPPacket *pkt)
{
    int ret, old_flv_size, type;
    const uint8_t *next;
    uint8_t *p;
    uint32_t size;
    uint32_t ts, cts, pts = 0;

    old_flv_size = update_offset(rt, pkt->size);

    if ((ret = av_reallocp(&rt->flv_data, rt->flv_size)) < 0) {
        rt->flv_size = rt->flv_off = 0;
        return ret;
    }

    next = pkt->data;
    p    = rt->flv_data + old_flv_size;

    /* copy data while rewriting timestamps */
    ts = pkt->timestamp;

    while (next - pkt->data < pkt->size - RTMP_HEADER) {
        type = bytestream_get_byte(&next);
        size = bytestream_get_be24(&next);
        cts  = bytestream_get_be24(&next);
        cts |= bytestream_get_byte(&next) << 24;
        if (!pts)
            pts = cts;
        ts += cts - pts;
        pts = cts;
        if (size + 3 + 4 > pkt->data + pkt->size - next)
            break;
        bytestream_put_byte(&p, type);
        bytestream_put_be24(&p, size);
        bytestream_put_be24(&p, ts);
        bytestream_put_byte(&p, ts >> 24);
        memcpy(p, next, size + 3 + 4);
        p    += size + 3;
        bytestream_put_be32(&p, size + RTMP_HEADER);
        next += size + 3 + 4;
    }
    if (p != rt->flv_data + rt->flv_size) {
        av_log(rt, AV_LOG_WARNING, "Incomplete flv packets in "
                                     "RTMP_PT_METADATA packet\n");
        rt->flv_size = p - rt->flv_data;
    }

    return 0;
}