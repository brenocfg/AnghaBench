#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nv04_crtc_reg {int /*<<< orphan*/ * CRTC; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVReadVgaCrtc (struct drm_device*,int,int) ; 

__attribute__((used)) static void
rd_cio_state(struct drm_device *dev, int head,
	     struct nv04_crtc_reg *crtcstate, int index)
{
	crtcstate->CRTC[index] = NVReadVgaCrtc(dev, head, index);
}