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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct nouveau_encoder {int /*<<< orphan*/  dcb; TYPE_1__ restore; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  nv04_dfp_get_bound_head (struct drm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 

__attribute__((used)) static void nv04_dfp_save(struct drm_encoder *encoder)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct drm_device *dev = encoder->dev;

	if (nv_two_heads(dev))
		nv_encoder->restore.head =
			nv04_dfp_get_bound_head(dev, nv_encoder->dcb);
}