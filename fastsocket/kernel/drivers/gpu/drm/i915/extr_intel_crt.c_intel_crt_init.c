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
struct TYPE_2__ {int cloneable; int crtc_mask; int /*<<< orphan*/  base; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  enable; int /*<<< orphan*/  disable; int /*<<< orphan*/  type; } ;
struct intel_crt {scalar_t__ force_hotplug_required; TYPE_1__ base; int /*<<< orphan*/  adpa_reg; struct intel_connector* connector; } ;
struct drm_connector {int interlace_allowed; int /*<<< orphan*/  polled; scalar_t__ doublescan_allowed; } ;
struct intel_connector {int /*<<< orphan*/  get_hw_state; struct drm_connector base; } ;
struct drm_i915_private {int fdi_rx_config; int /*<<< orphan*/  hotplug_supported_mask; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPA ; 
 int /*<<< orphan*/  CRT_HOTPLUG_INT_STATUS ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_CONNECT ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int FDI_RX_LINK_REVERSAL_OVERRIDE ; 
 int FDI_RX_POLARITY_REVERSED_LPT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HAS_DDI (struct drm_device*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_device*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_I830 (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  PCH_ADPA ; 
 int /*<<< orphan*/  VLV_ADPA ; 
 int /*<<< orphan*/  _FDI_RXA_CTL ; 
 int /*<<< orphan*/  crt_encoder_funcs ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sysfs_connector_add (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,TYPE_1__*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_crt_connector_funcs ; 
 int /*<<< orphan*/  intel_crt_connector_helper_funcs ; 
 int /*<<< orphan*/  intel_crt_enc_funcs ; 
 int /*<<< orphan*/  intel_crt_get_hw_state ; 
 int /*<<< orphan*/  intel_ddi_get_hw_state ; 
 int /*<<< orphan*/  intel_disable_crt ; 
 int /*<<< orphan*/  intel_enable_crt ; 
 int /*<<< orphan*/  intel_no_crt ; 
 int /*<<< orphan*/  kfree (struct intel_crt*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

void intel_crt_init(struct drm_device *dev)
{
	struct drm_connector *connector;
	struct intel_crt *crt;
	struct intel_connector *intel_connector;
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* Skip machines without VGA that falsely report hotplug events */
	if (dmi_check_system(intel_no_crt))
		return;

	crt = kzalloc(sizeof(struct intel_crt), GFP_KERNEL);
	if (!crt)
		return;

	intel_connector = kzalloc(sizeof(struct intel_connector), GFP_KERNEL);
	if (!intel_connector) {
		kfree(crt);
		return;
	}

	connector = &intel_connector->base;
	crt->connector = intel_connector;
	drm_connector_init(dev, &intel_connector->base,
			   &intel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	drm_encoder_init(dev, &crt->base.base, &intel_crt_enc_funcs,
			 DRM_MODE_ENCODER_DAC);

	intel_connector_attach_encoder(intel_connector, &crt->base);

	crt->base.type = INTEL_OUTPUT_ANALOG;
	crt->base.cloneable = true;
	if (IS_I830(dev))
		crt->base.crtc_mask = (1 << 0);
	else
		crt->base.crtc_mask = (1 << 0) | (1 << 1) | (1 << 2);

	if (IS_GEN2(dev))
		connector->interlace_allowed = 0;
	else
		connector->interlace_allowed = 1;
	connector->doublescan_allowed = 0;

	if (HAS_PCH_SPLIT(dev))
		crt->adpa_reg = PCH_ADPA;
	else if (IS_VALLEYVIEW(dev))
		crt->adpa_reg = VLV_ADPA;
	else
		crt->adpa_reg = ADPA;

	crt->base.disable = intel_disable_crt;
	crt->base.enable = intel_enable_crt;
	if (HAS_DDI(dev))
		crt->base.get_hw_state = intel_ddi_get_hw_state;
	else
		crt->base.get_hw_state = intel_crt_get_hw_state;
	intel_connector->get_hw_state = intel_connector_get_hw_state;

	drm_encoder_helper_add(&crt->base.base, &crt_encoder_funcs);
	drm_connector_helper_add(connector, &intel_crt_connector_helper_funcs);

	drm_sysfs_connector_add(connector);

	if (I915_HAS_HOTPLUG(dev))
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	else
		connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	/*
	 * Configure the automatic hotplug detection stuff
	 */
	crt->force_hotplug_required = 0;

	dev_priv->hotplug_supported_mask |= CRT_HOTPLUG_INT_STATUS;

	/*
	 * TODO: find a proper way to discover whether we need to set the the
	 * polarity and link reversal bits or not, instead of relying on the
	 * BIOS.
	 */
	if (HAS_PCH_LPT(dev)) {
		u32 fdi_config = FDI_RX_POLARITY_REVERSED_LPT |
				 FDI_RX_LINK_REVERSAL_OVERRIDE;

		dev_priv->fdi_rx_config = I915_READ(_FDI_RXA_CTL) & fdi_config;
	}
}