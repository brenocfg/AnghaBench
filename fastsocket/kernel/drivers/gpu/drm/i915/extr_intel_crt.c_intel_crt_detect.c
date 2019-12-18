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
struct intel_load_detect_pipe {int dummy; } ;
struct intel_crt {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int status; struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_device*) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct intel_crt* intel_attached_crt (struct drm_connector*) ; 
 scalar_t__ intel_crt_detect_ddc (struct drm_connector*) ; 
 scalar_t__ intel_crt_detect_hotplug (struct drm_connector*) ; 
 int intel_crt_load_detect (struct intel_crt*) ; 
 scalar_t__ intel_get_load_detect_pipe (struct drm_connector*,int /*<<< orphan*/ *,struct intel_load_detect_pipe*) ; 
 int /*<<< orphan*/  intel_release_load_detect_pipe (struct drm_connector*,struct intel_load_detect_pipe*) ; 

__attribute__((used)) static enum drm_connector_status
intel_crt_detect(struct drm_connector *connector, bool force)
{
	struct drm_device *dev = connector->dev;
	struct intel_crt *crt = intel_attached_crt(connector);
	enum drm_connector_status status;
	struct intel_load_detect_pipe tmp;

	if (I915_HAS_HOTPLUG(dev)) {
		/* We can not rely on the HPD pin always being correctly wired
		 * up, for example many KVM do not pass it through, and so
		 * only trust an assertion that the monitor is connected.
		 */
		if (intel_crt_detect_hotplug(connector)) {
			DRM_DEBUG_KMS("CRT detected via hotplug\n");
			return connector_status_connected;
		} else
			DRM_DEBUG_KMS("CRT not detected via hotplug\n");
	}

	if (intel_crt_detect_ddc(connector))
		return connector_status_connected;

	/* Load detection is broken on HPD capable machines. Whoever wants a
	 * broken monitor (without edid) to work behind a broken kvm (that fails
	 * to have the right resistors for HP detection) needs to fix this up.
	 * For now just bail out. */
	if (I915_HAS_HOTPLUG(dev))
		return connector_status_disconnected;

	if (!force)
		return connector->status;

	/* for pre-945g platforms use load detect */
	if (intel_get_load_detect_pipe(connector, NULL, &tmp)) {
		if (intel_crt_detect_ddc(connector))
			status = connector_status_connected;
		else
			status = intel_crt_load_detect(crt);
		intel_release_load_detect_pipe(connector, &tmp);
	} else
		status = connector_status_unknown;

	return status;
}