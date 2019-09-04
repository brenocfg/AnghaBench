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
struct TYPE_9__ {TYPE_3__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  ext_buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  InputStream; } ;
struct TYPE_8__ {TYPE_2__ qsv_param; TYPE_1__ comp_conf; int /*<<< orphan*/  fs; int /*<<< orphan*/  qsv; } ;
typedef  TYPE_3__ QSVOverlayContext ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_framesync_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_qsvvpp_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void overlay_qsv_uninit(AVFilterContext *ctx)
{
    QSVOverlayContext *vpp = ctx->priv;

    ff_qsvvpp_free(&vpp->qsv);
    ff_framesync_uninit(&vpp->fs);
    av_freep(&vpp->comp_conf.InputStream);
    av_freep(&vpp->qsv_param.ext_buf);
}