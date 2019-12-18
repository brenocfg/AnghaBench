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
struct drm_file {int authenticated; int /*<<< orphan*/  master; } ;
struct drm_device {int dummy; } ;
struct drm_auth {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct drm_file* drm_find_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_remove_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_authmagic(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	struct drm_auth *auth = data;
	struct drm_file *file;

	DRM_DEBUG("%u\n", auth->magic);
	if ((file = drm_find_file(file_priv->master, auth->magic))) {
		file->authenticated = 1;
		drm_remove_magic(file_priv->master, auth->magic);
		return 0;
	}
	return -EINVAL;
}