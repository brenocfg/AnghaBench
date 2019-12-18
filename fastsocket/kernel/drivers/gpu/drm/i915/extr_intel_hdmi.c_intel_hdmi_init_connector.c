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
typedef  int u32 ;
struct intel_hdmi {int /*<<< orphan*/  set_infoframes; int /*<<< orphan*/  write_infoframe; int /*<<< orphan*/  ddc_bus; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_digital_port {int port; struct intel_encoder base; struct intel_hdmi hdmi; } ;
struct drm_connector {int interlace_allowed; scalar_t__ doublescan_allowed; int /*<<< orphan*/  polled; } ;
struct intel_connector {int /*<<< orphan*/  get_hw_state; struct drm_connector base; } ;
struct drm_i915_private {int /*<<< orphan*/  hotplug_supported_mask; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int /*<<< orphan*/  GMBUS_PORT_DPB ; 
 int /*<<< orphan*/  GMBUS_PORT_DPC ; 
 int /*<<< orphan*/  GMBUS_PORT_DPD ; 
 scalar_t__ HAS_DDI (struct drm_device*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_device*) ; 
 int /*<<< orphan*/  HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 int /*<<< orphan*/  IS_GM45 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  PEG_BAND_GAP_DATA ; 
 int /*<<< orphan*/  PORTB_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  PORTC_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  PORTD_HOTPLUG_INT_STATUS ; 
#define  PORT_A 131 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int /*<<< orphan*/  cpt_set_infoframes ; 
 int /*<<< orphan*/  cpt_write_infoframe ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sysfs_connector_add (struct drm_connector*) ; 
 int /*<<< orphan*/  g4x_set_infoframes ; 
 int /*<<< orphan*/  g4x_write_infoframe ; 
 int /*<<< orphan*/  hsw_set_infoframes ; 
 int /*<<< orphan*/  hsw_write_infoframe ; 
 int /*<<< orphan*/  ibx_set_infoframes ; 
 int /*<<< orphan*/  ibx_write_infoframe ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_ddi_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_hdmi_add_properties (struct intel_hdmi*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_connector_funcs ; 
 int /*<<< orphan*/  intel_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  vlv_set_infoframes ; 
 int /*<<< orphan*/  vlv_write_infoframe ; 

void intel_hdmi_init_connector(struct intel_digital_port *intel_dig_port,
			       struct intel_connector *intel_connector)
{
	struct drm_connector *connector = &intel_connector->base;
	struct intel_hdmi *intel_hdmi = &intel_dig_port->hdmi;
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_device *dev = intel_encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum port port = intel_dig_port->port;

	drm_connector_init(dev, connector, &intel_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_HDMIA);
	drm_connector_helper_add(connector, &intel_hdmi_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_HPD;
	connector->interlace_allowed = 1;
	connector->doublescan_allowed = 0;

	switch (port) {
	case PORT_B:
		intel_hdmi->ddc_bus = GMBUS_PORT_DPB;
		dev_priv->hotplug_supported_mask |= PORTB_HOTPLUG_INT_STATUS;
		break;
	case PORT_C:
		intel_hdmi->ddc_bus = GMBUS_PORT_DPC;
		dev_priv->hotplug_supported_mask |= PORTC_HOTPLUG_INT_STATUS;
		break;
	case PORT_D:
		intel_hdmi->ddc_bus = GMBUS_PORT_DPD;
		dev_priv->hotplug_supported_mask |= PORTD_HOTPLUG_INT_STATUS;
		break;
	case PORT_A:
		/* Internal port only for eDP. */
	default:
		BUG();
	}

	if (!HAS_PCH_SPLIT(dev)) {
		intel_hdmi->write_infoframe = g4x_write_infoframe;
		intel_hdmi->set_infoframes = g4x_set_infoframes;
	} else if (IS_VALLEYVIEW(dev)) {
		intel_hdmi->write_infoframe = vlv_write_infoframe;
		intel_hdmi->set_infoframes = vlv_set_infoframes;
	} else if (IS_HASWELL(dev)) {
		intel_hdmi->write_infoframe = hsw_write_infoframe;
		intel_hdmi->set_infoframes = hsw_set_infoframes;
	} else if (HAS_PCH_IBX(dev)) {
		intel_hdmi->write_infoframe = ibx_write_infoframe;
		intel_hdmi->set_infoframes = ibx_set_infoframes;
	} else {
		intel_hdmi->write_infoframe = cpt_write_infoframe;
		intel_hdmi->set_infoframes = cpt_set_infoframes;
	}

	if (HAS_DDI(dev))
		intel_connector->get_hw_state = intel_ddi_connector_get_hw_state;
	else
		intel_connector->get_hw_state = intel_connector_get_hw_state;

	intel_hdmi_add_properties(intel_hdmi, connector);

	intel_connector_attach_encoder(intel_connector, intel_encoder);
	drm_sysfs_connector_add(connector);

	/* For G4X desktop chip, PEG_BAND_GAP_DATA 3:0 must first be written
	 * 0xd.  Failure to do so will result in spurious interrupts being
	 * generated on the port when a cable is not attached.
	 */
	if (IS_G4X(dev) && !IS_GM45(dev)) {
		u32 temp = I915_READ(PEG_BAND_GAP_DATA);
		I915_WRITE(PEG_BAND_GAP_DATA, (temp & ~0xf) | 0xd);
	}
}