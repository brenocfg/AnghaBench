#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int /*<<< orphan*/ * nb_prev_pkt; int /*<<< orphan*/ * prev_pkt; int /*<<< orphan*/  out_chunk_size; int /*<<< orphan*/  stream; int /*<<< orphan*/  nb_streamid; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;
typedef  int /*<<< orphan*/  PutByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  RTMP_NETWORK_CHANNEL ; 
 int /*<<< orphan*/  RTMP_PT_USER_CONTROL ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_rtmp_packet_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_2__*) ; 
 int ff_rtmp_packet_write (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_begin(URLContext *s)
{
    RTMPContext *rt = s->priv_data;
    PutByteContext pbc;
    RTMPPacket spkt = { 0 };
    int ret;

    // Send Stream Begin 1
    if ((ret = ff_rtmp_packet_create(&spkt, RTMP_NETWORK_CHANNEL,
                                     RTMP_PT_USER_CONTROL, 0, 6)) < 0) {
        av_log(s, AV_LOG_ERROR, "Unable to create response packet\n");
        return ret;
    }

    bytestream2_init_writer(&pbc, spkt.data, spkt.size);
    bytestream2_put_be16(&pbc, 0);          // 0 -> Stream Begin
    bytestream2_put_be32(&pbc, rt->nb_streamid);

    ret = ff_rtmp_packet_write(rt->stream, &spkt, rt->out_chunk_size,
                               &rt->prev_pkt[1], &rt->nb_prev_pkt[1]);

    ff_rtmp_packet_destroy(&spkt);

    return ret;
}