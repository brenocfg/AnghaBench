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
struct nouveau_framebuffer {TYPE_1__* nvbo; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int
nouveau_user_framebuffer_create_handle(struct drm_framebuffer *drm_fb,
				       struct drm_file *file_priv,
				       unsigned int *handle)
{
	struct nouveau_framebuffer *fb = nouveau_framebuffer(drm_fb);

	return drm_gem_handle_create(file_priv, fb->nvbo->gem, handle);
}