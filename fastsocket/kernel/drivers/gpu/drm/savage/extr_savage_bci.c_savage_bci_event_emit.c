#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int event_wrap; } ;
typedef  TYPE_1__ drm_savage_private_t ;
struct TYPE_5__ {int count; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ drm_savage_event_emit_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int savage_bci_emit_event (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int savage_bci_event_emit(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_savage_private_t *dev_priv = dev->dev_private;
	drm_savage_event_emit_t *event = data;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	event->count = savage_bci_emit_event(dev_priv, event->flags);
	event->count |= dev_priv->event_wrap << 16;

	return 0;
}