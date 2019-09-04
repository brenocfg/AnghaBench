#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; } ;
struct TYPE_5__ {TYPE_2__* opaque; } ;
typedef  TYPE_1__ MpegTSSection ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  TS_PACKET_SIZE ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpegts_prefix_m2ts_header (TYPE_2__*) ; 

__attribute__((used)) static void section_write_packet(MpegTSSection *s, const uint8_t *packet)
{
    AVFormatContext *ctx = s->opaque;
    mpegts_prefix_m2ts_header(ctx);
    avio_write(ctx->pb, packet, TS_PACKET_SIZE);
}