#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nouveau_bo {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct nouveau_bo* sync; } ;

/* Variables and functions */
 TYPE_1__* nv50_disp (struct drm_device*) ; 

struct nouveau_bo *
nv50_display_crtc_sema(struct drm_device *dev, int crtc)
{
	return nv50_disp(dev)->sync;
}