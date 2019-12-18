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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  stream_index; scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int seen_sequence_header; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 scalar_t__ DIRAC_DATA_UNIT_HEADER_SIZE ; 
 int av_new_packet (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  fill_parse_info_header (TYPE_1__*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int vc2hq_handle_sequence_header(PayloadContext *pl_ctx, AVStream *st, AVPacket *pkt,
                                        const uint8_t *buf, int len)
{
    int res;
    uint32_t size = DIRAC_DATA_UNIT_HEADER_SIZE + len;

    if ((res = av_new_packet(pkt, DIRAC_DATA_UNIT_HEADER_SIZE + len)) < 0)
        return res;

    fill_parse_info_header(pl_ctx, pkt->data, 0x00, size);
    /* payload of seq. header */
    memcpy(pkt->data + DIRAC_DATA_UNIT_HEADER_SIZE, buf, len);
    pkt->stream_index = st->index;

    pl_ctx->seen_sequence_header = 1;

    return 0;
}