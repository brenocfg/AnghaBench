#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int packet_size; int vcd_padding_bytes_written; int /*<<< orphan*/  packet_number; } ;
typedef  TYPE_1__ MpegMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_vcd_padding_sector(AVFormatContext *ctx)
{
    /* There are two ways to do this padding: writing a sector/pack
     * of 0 values, or writing an MPEG padding pack. Both seem to
     * work with most decoders, BUT the VCD standard only allows a 0-sector
     * (see standard p. IV-4, IV-5).
     * So a 0-sector it is... */

    MpegMuxContext *s = ctx->priv_data;
    int i;

    for (i = 0; i < s->packet_size; i++)
        avio_w8(ctx->pb, 0);

    s->vcd_padding_bytes_written += s->packet_size;

    avio_flush(ctx->pb);

    /* increasing the packet number is correct. The SCR of the following packs
     * is calculated from the packet_number and it has to include the padding
     * sector (it represents the sector index, not the MPEG pack index)
     * (see VCD standard p. IV-6) */
    s->packet_number++;
}