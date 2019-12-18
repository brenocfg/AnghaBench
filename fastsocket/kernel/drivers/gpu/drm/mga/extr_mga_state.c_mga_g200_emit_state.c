#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int dirty; scalar_t__ warp_pipe; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_8__ {scalar_t__ warp_pipe; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;

/* Variables and functions */
 unsigned int MGA_UPLOAD_CONTEXT ; 
 unsigned int MGA_UPLOAD_TEX0 ; 
 int /*<<< orphan*/  mga_g200_emit_context (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_g200_emit_pipe (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_g200_emit_tex0 (TYPE_2__*) ; 

__attribute__((used)) static void mga_g200_emit_state(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned int dirty = sarea_priv->dirty;

	if (sarea_priv->warp_pipe != dev_priv->warp_pipe) {
		mga_g200_emit_pipe(dev_priv);
		dev_priv->warp_pipe = sarea_priv->warp_pipe;
	}

	if (dirty & MGA_UPLOAD_CONTEXT) {
		mga_g200_emit_context(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_CONTEXT;
	}

	if (dirty & MGA_UPLOAD_TEX0) {
		mga_g200_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_TEX0;
	}
}