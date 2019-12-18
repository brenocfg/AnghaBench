#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct intel_dp {int output_reg; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_digital_port {int port; TYPE_2__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  pm_qos; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_6__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int DPA_AUX_CH_CTL ; 
 int DPA_AUX_CH_DATA1 ; 
 int DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT ; 
 int DP_AUX_CH_CTL_DONE ; 
 int DP_AUX_CH_CTL_INTERRUPT ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_MASK ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT ; 
 int DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT ; 
 int DP_AUX_CH_CTL_RECEIVE_ERROR ; 
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int DP_AUX_CH_CTL_TIME_OUT_400us ; 
 int DP_AUX_CH_CTL_TIME_OUT_ERROR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EBUSY ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ HAS_DDI (struct drm_device*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  I915_READ (int) ; 
 int I915_READ_NOTRACE (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 TYPE_3__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int PCH_DPB_AUX_CH_CTL ; 
 int PCH_DPB_AUX_CH_DATA1 ; 
 int PCH_DPC_AUX_CH_CTL ; 
 int PCH_DPC_AUX_CH_DATA1 ; 
 int PCH_DPD_AUX_CH_CTL ; 
 int PCH_DPD_AUX_CH_DATA1 ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
#define  PORT_A 131 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int intel_ddi_get_cdclk_freq (struct drm_i915_private*) ; 
 int intel_dp_aux_wait_done (struct intel_dp*,int) ; 
 int /*<<< orphan*/  intel_dp_check_edp (struct intel_dp*) ; 
 int intel_hrawclk (struct drm_device*) ; 
 int /*<<< orphan*/  intel_pch_rawclk (struct drm_device*) ; 
 scalar_t__ is_cpu_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pack_aux (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
intel_dp_aux_ch(struct intel_dp *intel_dp,
		uint8_t *send, int send_bytes,
		uint8_t *recv, int recv_size)
{
	uint32_t output_reg = intel_dp->output_reg;
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t ch_ctl = output_reg + 0x10;
	uint32_t ch_data = ch_ctl + 4;
	int i, ret, recv_bytes;
	uint32_t status;
	uint32_t aux_clock_divider;
	int try, precharge;
	bool has_aux_irq = INTEL_INFO(dev)->gen >= 5 && !IS_VALLEYVIEW(dev);

	/* dp aux is extremely sensitive to irq latency, hence request the
	 * lowest possible wakeup latency and so prevent the cpu from going into
	 * deep sleep states.
	 */
	pm_qos_update_request(&dev_priv->pm_qos, 0);

	if (IS_HASWELL(dev)) {
		switch (intel_dig_port->port) {
		case PORT_A:
			ch_ctl = DPA_AUX_CH_CTL;
			ch_data = DPA_AUX_CH_DATA1;
			break;
		case PORT_B:
			ch_ctl = PCH_DPB_AUX_CH_CTL;
			ch_data = PCH_DPB_AUX_CH_DATA1;
			break;
		case PORT_C:
			ch_ctl = PCH_DPC_AUX_CH_CTL;
			ch_data = PCH_DPC_AUX_CH_DATA1;
			break;
		case PORT_D:
			ch_ctl = PCH_DPD_AUX_CH_CTL;
			ch_data = PCH_DPD_AUX_CH_DATA1;
			break;
		default:
			BUG();
		}
	}

	intel_dp_check_edp(intel_dp);
	/* The clock divider is based off the hrawclk,
	 * and would like to run at 2MHz. So, take the
	 * hrawclk value and divide by 2 and use that
	 *
	 * Note that PCH attached eDP panels should use a 125MHz input
	 * clock divider.
	 */
	if (is_cpu_edp(intel_dp)) {
		if (HAS_DDI(dev))
			aux_clock_divider = intel_ddi_get_cdclk_freq(dev_priv) >> 1;
		else if (IS_VALLEYVIEW(dev))
			aux_clock_divider = 100;
		else if (IS_GEN6(dev) || IS_GEN7(dev))
			aux_clock_divider = 200; /* SNB & IVB eDP input clock at 400Mhz */
		else
			aux_clock_divider = 225; /* eDP input clock at 450Mhz */
	} else if (HAS_PCH_SPLIT(dev))
		aux_clock_divider = DIV_ROUND_UP(intel_pch_rawclk(dev), 2);
	else
		aux_clock_divider = intel_hrawclk(dev) / 2;

	if (IS_GEN6(dev))
		precharge = 3;
	else
		precharge = 5;

	/* Try to wait for any previous AUX channel activity */
	for (try = 0; try < 3; try++) {
		status = I915_READ_NOTRACE(ch_ctl);
		if ((status & DP_AUX_CH_CTL_SEND_BUSY) == 0)
			break;
		msleep(1);
	}

	if (try == 3) {
		WARN(1, "dp_aux_ch not started status 0x%08x\n",
		     I915_READ(ch_ctl));
		ret = -EBUSY;
		goto out;
	}

	/* Must try at least 3 times according to DP spec */
	for (try = 0; try < 5; try++) {
		/* Load the send data into the aux channel data registers */
		for (i = 0; i < send_bytes; i += 4)
			I915_WRITE(ch_data + i,
				   pack_aux(send + i, send_bytes - i));

		/* Send the command and wait for it to complete */
		I915_WRITE(ch_ctl,
			   DP_AUX_CH_CTL_SEND_BUSY |
			   (has_aux_irq ? DP_AUX_CH_CTL_INTERRUPT : 0) |
			   DP_AUX_CH_CTL_TIME_OUT_400us |
			   (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
			   (precharge << DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT) |
			   (aux_clock_divider << DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT) |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);

		status = intel_dp_aux_wait_done(intel_dp, has_aux_irq);

		/* Clear done status and any errors */
		I915_WRITE(ch_ctl,
			   status |
			   DP_AUX_CH_CTL_DONE |
			   DP_AUX_CH_CTL_TIME_OUT_ERROR |
			   DP_AUX_CH_CTL_RECEIVE_ERROR);

		if (status & (DP_AUX_CH_CTL_TIME_OUT_ERROR |
			      DP_AUX_CH_CTL_RECEIVE_ERROR))
			continue;
		if (status & DP_AUX_CH_CTL_DONE)
			break;
	}

	if ((status & DP_AUX_CH_CTL_DONE) == 0) {
		DRM_ERROR("dp_aux_ch not done status 0x%08x\n", status);
		ret = -EBUSY;
		goto out;
	}

	/* Check for timeout or receive error.
	 * Timeouts occur when the sink is not connected
	 */
	if (status & DP_AUX_CH_CTL_RECEIVE_ERROR) {
		DRM_ERROR("dp_aux_ch receive error status 0x%08x\n", status);
		ret = -EIO;
		goto out;
	}

	/* Timeouts occur when the device isn't connected, so they're
	 * "normal" -- don't fill the kernel log with these */
	if (status & DP_AUX_CH_CTL_TIME_OUT_ERROR) {
		DRM_DEBUG_KMS("dp_aux_ch timeout status 0x%08x\n", status);
		ret = -ETIMEDOUT;
		goto out;
	}

	/* Unload any bytes sent back from the other side */
	recv_bytes = ((status & DP_AUX_CH_CTL_MESSAGE_SIZE_MASK) >>
		      DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT);
	if (recv_bytes > recv_size)
		recv_bytes = recv_size;

	for (i = 0; i < recv_bytes; i += 4)
		unpack_aux(I915_READ(ch_data + i),
			   recv + i, recv_bytes - i);

	ret = recv_bytes;
out:
	pm_qos_update_request(&dev_priv->pm_qos, PM_QOS_DEFAULT_VALUE);

	return ret;
}