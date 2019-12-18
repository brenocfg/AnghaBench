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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  sub_pkt; int /*<<< orphan*/  sub_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  time_base; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVIStream ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  INT64_MIN ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ avformat_seek_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_read_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seek_subtitle(AVStream *st, AVStream *st2, int64_t timestamp)
{
    AVIStream *ast2 = st2->priv_data;
    int64_t ts2     = av_rescale_q(timestamp, st->time_base, st2->time_base);
    av_packet_unref(&ast2->sub_pkt);
    if (avformat_seek_file(ast2->sub_ctx, 0, INT64_MIN, ts2, ts2, 0) >= 0 ||
        avformat_seek_file(ast2->sub_ctx, 0, ts2, ts2, INT64_MAX, 0) >= 0)
        ff_read_packet(ast2->sub_ctx, &ast2->sub_pkt);
}