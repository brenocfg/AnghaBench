#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ MemId; } ;
struct TYPE_9__ {TYPE_1__ Data; } ;
struct TYPE_12__ {TYPE_2__ surface; } ;
struct TYPE_11__ {int nb_mids; TYPE_3__* mids; } ;
struct TYPE_10__ {scalar_t__ handle; } ;
typedef  TYPE_3__ QSVMid ;
typedef  TYPE_4__ QSVFramesContext ;
typedef  TYPE_5__ QSVFrame ;

/* Variables and functions */
 int AVERROR_BUG ; 

int ff_qsv_find_surface_idx(QSVFramesContext *ctx, QSVFrame *frame)
{
    int i;
    for (i = 0; i < ctx->nb_mids; i++) {
        QSVMid *mid = &ctx->mids[i];
        if (mid->handle == frame->surface.Data.MemId)
            return i;
    }
    return AVERROR_BUG;
}