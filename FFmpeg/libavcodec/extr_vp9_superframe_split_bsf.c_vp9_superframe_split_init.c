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
struct TYPE_4__ {int /*<<< orphan*/  buffer_pkt; } ;
typedef  TYPE_1__ VP9SFSplitContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_packet_alloc () ; 

__attribute__((used)) static int vp9_superframe_split_init(AVBSFContext *ctx)
{
    VP9SFSplitContext *s = ctx->priv_data;

    s->buffer_pkt = av_packet_alloc();
    if (!s->buffer_pkt)
        return AVERROR(ENOMEM);

    return 0;
}