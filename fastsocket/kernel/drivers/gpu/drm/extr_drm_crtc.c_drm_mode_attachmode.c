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
struct drm_display_mode {int /*<<< orphan*/  head; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  user_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_mode_attachmode(struct drm_device *dev,
				struct drm_connector *connector,
				struct drm_display_mode *mode)
{
	list_add_tail(&mode->head, &connector->user_modes);
}