#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int has_audio; int has_video; scalar_t__ flv_size; int /*<<< orphan*/  flv_data; scalar_t__ flv_off; } ;
struct TYPE_6__ {int size; int timestamp; int type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;
typedef  int /*<<< orphan*/  PutByteContext ;

/* Variables and functions */
 scalar_t__ RTMP_HEADER ; 
 int RTMP_PT_AUDIO ; 
 int RTMP_PT_VIDEO ; 
 int av_reallocp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_put_be24 (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  bytestream2_put_be32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_put_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_skip_p (int /*<<< orphan*/ *,int) ; 
 int update_offset (TYPE_2__*,int const) ; 

__attribute__((used)) static int append_flv_data(RTMPContext *rt, RTMPPacket *pkt, int skip)
{
    int old_flv_size, ret;
    PutByteContext pbc;
    const uint8_t *data = pkt->data + skip;
    const int size      = pkt->size - skip;
    uint32_t ts         = pkt->timestamp;

    if (pkt->type == RTMP_PT_AUDIO) {
        rt->has_audio = 1;
    } else if (pkt->type == RTMP_PT_VIDEO) {
        rt->has_video = 1;
    }

    old_flv_size = update_offset(rt, size + 15);

    if ((ret = av_reallocp(&rt->flv_data, rt->flv_size)) < 0) {
        rt->flv_size = rt->flv_off = 0;
        return ret;
    }
    bytestream2_init_writer(&pbc, rt->flv_data, rt->flv_size);
    bytestream2_skip_p(&pbc, old_flv_size);
    bytestream2_put_byte(&pbc, pkt->type);
    bytestream2_put_be24(&pbc, size);
    bytestream2_put_be24(&pbc, ts);
    bytestream2_put_byte(&pbc, ts >> 24);
    bytestream2_put_be24(&pbc, 0);
    bytestream2_put_buffer(&pbc, data, size);
    bytestream2_put_be32(&pbc, size + RTMP_HEADER);

    return 0;
}