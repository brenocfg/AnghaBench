#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data_UID; scalar_t__ palette_UID; scalar_t__ depth_UID; scalar_t__ gxm_rtgt; } ;
typedef  TYPE_1__ vita2d_texture ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gpu_free (scalar_t__) ; 
 int /*<<< orphan*/  sceGxmDestroyRenderTarget (scalar_t__) ; 

void vita2d_free_texture(vita2d_texture *texture)
{
	if (texture) {
		if (texture->gxm_rtgt) {
			sceGxmDestroyRenderTarget(texture->gxm_rtgt);
		}
		if (texture->depth_UID) {
			gpu_free(texture->depth_UID);
		}
		if (texture->palette_UID) {
			gpu_free(texture->palette_UID);
		}
		gpu_free(texture->data_UID);
		free(texture);
	}
}