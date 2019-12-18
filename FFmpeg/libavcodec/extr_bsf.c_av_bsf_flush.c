#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* filter; TYPE_1__* internal; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* flush ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  buffer_pkt; scalar_t__ eof; } ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void av_bsf_flush(AVBSFContext *ctx)
{
    ctx->internal->eof = 0;

    av_packet_unref(ctx->internal->buffer_pkt);

    if (ctx->filter->flush)
        ctx->filter->flush(ctx);
}