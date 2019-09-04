#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* priv_data; TYPE_1__* codec; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ CodedBitstreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void ff_cbs_close(CodedBitstreamContext **ctx_ptr)
{
    CodedBitstreamContext *ctx = *ctx_ptr;

    if (!ctx)
        return;

    if (ctx->codec && ctx->codec->close)
        ctx->codec->close(ctx);

    av_freep(&ctx->priv_data);
    av_freep(ctx_ptr);
}