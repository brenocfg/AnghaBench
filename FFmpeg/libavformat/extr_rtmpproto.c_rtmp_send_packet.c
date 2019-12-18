#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_9__ {int /*<<< orphan*/ * nb_prev_pkt; int /*<<< orphan*/ * prev_pkt; int /*<<< orphan*/  out_chunk_size; int /*<<< orphan*/  stream; } ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ RTMP_PT_INVOKE ; 
 int add_tracked_method (TYPE_2__*,char*,double) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_amf_read_number (int /*<<< orphan*/ *,double*) ; 
 int ff_amf_read_string (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_1__*) ; 
 int ff_rtmp_packet_write (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtmp_send_packet(RTMPContext *rt, RTMPPacket *pkt, int track)
{
    int ret;

    if (pkt->type == RTMP_PT_INVOKE && track) {
        GetByteContext gbc;
        char name[128];
        double pkt_id;
        int len;

        bytestream2_init(&gbc, pkt->data, pkt->size);
        if ((ret = ff_amf_read_string(&gbc, name, sizeof(name), &len)) < 0)
            goto fail;

        if ((ret = ff_amf_read_number(&gbc, &pkt_id)) < 0)
            goto fail;

        if ((ret = add_tracked_method(rt, name, pkt_id)) < 0)
            goto fail;
    }

    ret = ff_rtmp_packet_write(rt->stream, pkt, rt->out_chunk_size,
                               &rt->prev_pkt[1], &rt->nb_prev_pkt[1]);
fail:
    ff_rtmp_packet_destroy(pkt);
    return ret;
}