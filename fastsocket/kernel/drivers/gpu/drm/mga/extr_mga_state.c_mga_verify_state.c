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
struct TYPE_6__ {unsigned int dirty; scalar_t__ nbox; scalar_t__ warp_pipe; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_7__ {scalar_t__ chipset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;

/* Variables and functions */
 scalar_t__ MGA_CARD_TYPE_G400 ; 
 scalar_t__ MGA_MAX_G200_PIPES ; 
 scalar_t__ MGA_MAX_G400_PIPES ; 
 scalar_t__ MGA_NR_SAREA_CLIPRECTS ; 
 unsigned int MGA_UPLOAD_CONTEXT ; 
 unsigned int MGA_UPLOAD_PIPE ; 
 unsigned int MGA_UPLOAD_TEX0 ; 
 unsigned int MGA_UPLOAD_TEX1 ; 
 int mga_verify_context (TYPE_2__*) ; 
 int mga_verify_tex (TYPE_2__*,int) ; 

__attribute__((used)) static int mga_verify_state(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned int dirty = sarea_priv->dirty;
	int ret = 0;

	if (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	if (dirty & MGA_UPLOAD_CONTEXT)
		ret |= mga_verify_context(dev_priv);

	if (dirty & MGA_UPLOAD_TEX0)
		ret |= mga_verify_tex(dev_priv, 0);

	if (dev_priv->chipset >= MGA_CARD_TYPE_G400) {
		if (dirty & MGA_UPLOAD_TEX1)
			ret |= mga_verify_tex(dev_priv, 1);

		if (dirty & MGA_UPLOAD_PIPE)
			ret |= (sarea_priv->warp_pipe > MGA_MAX_G400_PIPES);
	} else {
		if (dirty & MGA_UPLOAD_PIPE)
			ret |= (sarea_priv->warp_pipe > MGA_MAX_G200_PIPES);
	}

	return (ret == 0);
}