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
typedef  int u8 ;
typedef  int u32 ;
struct zd_chip {int pa_type; int patch_cck_gain; int patch_cr157; int patch_6m_band_edge; int new_phy_layout; int al2230s_bit; scalar_t__ link_led; int supports_tx_led; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_POD ; 
 scalar_t__ LED1 ; 
 scalar_t__ LED2 ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread32_locked (struct zd_chip*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_rf_name (int) ; 

__attribute__((used)) static int read_pod(struct zd_chip *chip, u8 *rf_type)
{
	int r;
	u32 value;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioread32_locked(chip, &value, E2P_POD);
	if (r)
		goto error;
	dev_dbg_f(zd_chip_dev(chip), "E2P_POD %#010x\n", value);

	/* FIXME: AL2230 handling (Bit 7 in POD) */
	*rf_type = value & 0x0f;
	chip->pa_type = (value >> 16) & 0x0f;
	chip->patch_cck_gain = (value >> 8) & 0x1;
	chip->patch_cr157 = (value >> 13) & 0x1;
	chip->patch_6m_band_edge = (value >> 21) & 0x1;
	chip->new_phy_layout = (value >> 31) & 0x1;
	chip->al2230s_bit = (value >> 7) & 0x1;
	chip->link_led = ((value >> 4) & 1) ? LED1 : LED2;
	chip->supports_tx_led = 1;
	if (value & (1 << 24)) { /* LED scenario */
		if (value & (1 << 29))
			chip->supports_tx_led = 0;
	}

	dev_dbg_f(zd_chip_dev(chip),
		"RF %s %#01x PA type %#01x patch CCK %d patch CR157 %d "
		"patch 6M %d new PHY %d link LED%d tx led %d\n",
		zd_rf_name(*rf_type), *rf_type,
		chip->pa_type, chip->patch_cck_gain,
		chip->patch_cr157, chip->patch_6m_band_edge,
		chip->new_phy_layout,
		chip->link_led == LED1 ? 1 : 2,
		chip->supports_tx_led);
	return 0;
error:
	*rf_type = 0;
	chip->pa_type = 0;
	chip->patch_cck_gain = 0;
	chip->patch_cr157 = 0;
	chip->patch_6m_band_edge = 0;
	chip->new_phy_layout = 0;
	return r;
}