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
struct nouveau_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct drm_encoder*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 TYPE_1__* get_slave_funcs (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct nouveau_encoder*) ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 

__attribute__((used)) static void nv04_dfp_destroy(struct drm_encoder *encoder)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);

	if (get_slave_funcs(encoder))
		get_slave_funcs(encoder)->destroy(encoder);

	drm_encoder_cleanup(encoder);
	kfree(nv_encoder);
}