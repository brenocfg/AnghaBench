#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  attributes; } ;
typedef  TYPE_2__ VAAPIFramesContext ;
struct TYPE_9__ {TYPE_1__* internal; TYPE_3__* hwctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  surface_ids; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ AVVAAPIFramesContext ;
typedef  TYPE_4__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    AVVAAPIFramesContext *avfc = hwfc->hwctx;
    VAAPIFramesContext    *ctx = hwfc->internal->priv;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}