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
struct drm_encoder {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 TYPE_1__* nouveau_encoder (struct drm_encoder*) ; 

__attribute__((used)) static struct drm_crtc *
nv50_display_crtc_get(struct drm_encoder *encoder)
{
	return nouveau_encoder(encoder)->crtc;
}