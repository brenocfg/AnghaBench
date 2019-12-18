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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct TYPE_9__ {scalar_t__ seen_sequence_header; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  DIRAC_DATA_UNIT_HEADER_SIZE ; 
 int av_new_packet (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_parse_info_header (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc2hq_mark_end_of_sequence(PayloadContext *pl_ctx, AVStream *st, AVPacket *pkt)
{
    int res;
    uint32_t size = 0;

    /* create A/V packet */
    if ((res = av_new_packet(pkt, DIRAC_DATA_UNIT_HEADER_SIZE)) < 0)
        return res;

    fill_parse_info_header(pl_ctx, pkt->data, 0x10, size);
    pkt->stream_index = st->index;

    pl_ctx->seen_sequence_header = 0;

    return 0;
}