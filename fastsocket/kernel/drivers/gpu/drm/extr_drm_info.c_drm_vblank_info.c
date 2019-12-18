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
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {int num_crtcs; int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/ * vblank_inmodeset; int /*<<< orphan*/ * last_vblank_wait; int /*<<< orphan*/ * vblank_refcount; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_vblank_count (struct drm_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

int drm_vblank_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_device *dev = node->minor->dev;
	int crtc;

	mutex_lock(&dev->struct_mutex);
	for (crtc = 0; crtc < dev->num_crtcs; crtc++) {
		seq_printf(m, "CRTC %d enable:     %d\n",
			   crtc, atomic_read(&dev->vblank_refcount[crtc]));
		seq_printf(m, "CRTC %d counter:    %d\n",
			   crtc, drm_vblank_count(dev, crtc));
		seq_printf(m, "CRTC %d last wait:  %d\n",
			   crtc, dev->last_vblank_wait[crtc]);
		seq_printf(m, "CRTC %d in modeset: %d\n",
			   crtc, dev->vblank_inmodeset[crtc]);
	}
	mutex_unlock(&dev->struct_mutex);
	return 0;
}