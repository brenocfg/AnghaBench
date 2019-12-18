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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xc5000_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xc_get_ADC_Envelope (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_buildversion (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_frame_lines (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_frequency_error (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_hsync_freq (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_lock_status (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_quality (struct xc5000_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_get_version (struct xc5000_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xc_wait (int) ; 

__attribute__((used)) static void xc_debug_dump(struct xc5000_priv *priv)
{
	u16 adc_envelope;
	u32 freq_error_hz = 0;
	u16 lock_status;
	u32 hsync_freq_hz = 0;
	u16 frame_lines;
	u16 quality;
	u8 hw_majorversion = 0, hw_minorversion = 0;
	u8 fw_majorversion = 0, fw_minorversion = 0;
	u16 fw_buildversion = 0;

	/* Wait for stats to stabilize.
	 * Frame Lines needs two frame times after initial lock
	 * before it is valid.
	 */
	xc_wait(100);

	xc_get_ADC_Envelope(priv,  &adc_envelope);
	dprintk(1, "*** ADC envelope (0-1023) = %d\n", adc_envelope);

	xc_get_frequency_error(priv, &freq_error_hz);
	dprintk(1, "*** Frequency error = %d Hz\n", freq_error_hz);

	xc_get_lock_status(priv,  &lock_status);
	dprintk(1, "*** Lock status (0-Wait, 1-Locked, 2-No-signal) = %d\n",
		lock_status);

	xc_get_version(priv,  &hw_majorversion, &hw_minorversion,
		&fw_majorversion, &fw_minorversion);
	xc_get_buildversion(priv,  &fw_buildversion);
	dprintk(1, "*** HW: V%02x.%02x, FW: V%02x.%02x.%04x\n",
		hw_majorversion, hw_minorversion,
		fw_majorversion, fw_minorversion, fw_buildversion);

	xc_get_hsync_freq(priv,  &hsync_freq_hz);
	dprintk(1, "*** Horizontal sync frequency = %d Hz\n", hsync_freq_hz);

	xc_get_frame_lines(priv,  &frame_lines);
	dprintk(1, "*** Frame lines = %d\n", frame_lines);

	xc_get_quality(priv,  &quality);
	dprintk(1, "*** Quality (0:<8dB, 7:>56dB) = %d\n", quality);
}