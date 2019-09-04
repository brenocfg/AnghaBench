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
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* clut_list; } ;
typedef  TYPE_1__ DVBSubContext ;
typedef  TYPE_2__ DVBSubCLUT ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 

__attribute__((used)) static void delete_cluts(DVBSubContext *ctx)
{
    while (ctx->clut_list) {
        DVBSubCLUT *clut = ctx->clut_list;

        ctx->clut_list = clut->next;

        av_freep(&clut);
    }
}