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
struct TYPE_6__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  prev_pkt; int /*<<< orphan*/  have_end; } ;
typedef  TYPE_1__ GIFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GIF_TRAILER ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gif_write_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gif_write_trailer(AVFormatContext *s)
{
    GIFContext *gif = s->priv_data;
    AVIOContext *pb = s->pb;

    if (!gif->prev_pkt)
        return AVERROR(EINVAL);

    gif_write_packet(s, NULL);

    if (!gif->have_end)
        avio_w8(pb, GIF_TRAILER);
    av_packet_free(&gif->prev_pkt);

    return 0;
}