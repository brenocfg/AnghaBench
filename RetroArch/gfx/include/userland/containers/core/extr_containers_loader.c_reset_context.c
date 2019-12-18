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
struct TYPE_6__ {TYPE_1__* priv; int /*<<< orphan*/ * drm; scalar_t__ tracks_num; int /*<<< orphan*/ * tracks; scalar_t__ capabilities; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
struct TYPE_5__ {int /*<<< orphan*/ * tmp_io; int /*<<< orphan*/ * pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/ * pf_write; int /*<<< orphan*/ * pf_read; int /*<<< orphan*/ * pf_close; int /*<<< orphan*/ * module; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_assert (TYPE_2__*) ; 

__attribute__((used)) static void reset_context(VC_CONTAINER_T *p_ctx)
{
   vc_container_assert(p_ctx);

   p_ctx->capabilities = 0;
   p_ctx->tracks = NULL;
   p_ctx->tracks_num = 0;
   p_ctx->drm = NULL;
   p_ctx->priv->module = NULL;
   p_ctx->priv->pf_close = NULL;
   p_ctx->priv->pf_read = NULL;
   p_ctx->priv->pf_write = NULL;
   p_ctx->priv->pf_seek = NULL;
   p_ctx->priv->pf_control = NULL;
   p_ctx->priv->tmp_io = NULL;
}