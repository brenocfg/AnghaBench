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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int /*<<< orphan*/  CH_DBG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ) ; 
 int SUNI1x10GEXP_BITMSK_TOP_EXPIRED ; 
 int SUNI1x10GEXP_BITMSK_TOP_PL4_ID_DOOL ; 
 int SUNI1x10GEXP_BITMSK_TOP_PL4_ID_ROOL ; 
 int SUNI1x10GEXP_BITMSK_TOP_PL4_IS_ROOL ; 
 int SUNI1x10GEXP_BITMSK_TOP_PL4_OUT_ROOL ; 
 int SUNI1x10GEXP_BITMSK_TOP_SXRA_EXPIRED ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_DEVICE_STATUS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm3393_mac_reset(adapter_t * adapter)
{
	u32 val;
	u32 x;
	u32 is_pl4_reset_finished;
	u32 is_pl4_outof_lock;
	u32 is_xaui_mabc_pll_locked;
	u32 successful_reset;
	int i;

	/* The following steps are required to properly reset
	 * the PM3393. This information is provided in the
	 * PM3393 datasheet (Issue 2: November 2002)
	 * section 13.1 -- Device Reset.
	 *
	 * The PM3393 has three types of components that are
	 * individually reset:
	 *
	 * DRESETB      - Digital circuitry
	 * PL4_ARESETB  - PL4 analog circuitry
	 * XAUI_ARESETB - XAUI bus analog circuitry
	 *
	 * Steps to reset PM3393 using RSTB pin:
	 *
	 * 1. Assert RSTB pin low ( write 0 )
	 * 2. Wait at least 1ms to initiate a complete initialization of device.
	 * 3. Wait until all external clocks and REFSEL are stable.
	 * 4. Wait minimum of 1ms. (after external clocks and REFEL are stable)
	 * 5. De-assert RSTB ( write 1 )
	 * 6. Wait until internal timers to expires after ~14ms.
	 *    - Allows analog clock synthesizer(PL4CSU) to stabilize to
	 *      selected reference frequency before allowing the digital
	 *      portion of the device to operate.
	 * 7. Wait at least 200us for XAUI interface to stabilize.
	 * 8. Verify the PM3393 came out of reset successfully.
	 *    Set successful reset flag if everything worked else try again
	 *    a few more times.
	 */

	successful_reset = 0;
	for (i = 0; i < 3 && !successful_reset; i++) {
		/* 1 */
		t1_tpi_read(adapter, A_ELMER0_GPO, &val);
		val &= ~1;
		t1_tpi_write(adapter, A_ELMER0_GPO, val);

		/* 2 */
		msleep(1);

		/* 3 */
		msleep(1);

		/* 4 */
		msleep(2 /*1 extra ms for safety */ );

		/* 5 */
		val |= 1;
		t1_tpi_write(adapter, A_ELMER0_GPO, val);

		/* 6 */
		msleep(15 /*1 extra ms for safety */ );

		/* 7 */
		msleep(1);

		/* 8 */

		/* Has PL4 analog block come out of reset correctly? */
		t1_tpi_read(adapter, OFFSET(SUNI1x10GEXP_REG_DEVICE_STATUS), &val);
		is_pl4_reset_finished = (val & SUNI1x10GEXP_BITMSK_TOP_EXPIRED);

		/* TBD XXX SUNI1x10GEXP_BITMSK_TOP_PL4_IS_DOOL gets locked later in the init sequence
		 *         figure out why? */

		/* Have all PL4 block clocks locked? */
		x = (SUNI1x10GEXP_BITMSK_TOP_PL4_ID_DOOL
		     /*| SUNI1x10GEXP_BITMSK_TOP_PL4_IS_DOOL */  |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_ID_ROOL |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_IS_ROOL |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_OUT_ROOL);
		is_pl4_outof_lock = (val & x);

		/* ??? If this fails, might be able to software reset the XAUI part
		 *     and try to recover... thus saving us from doing another HW reset */
		/* Has the XAUI MABC PLL circuitry stablized? */
		is_xaui_mabc_pll_locked =
		    (val & SUNI1x10GEXP_BITMSK_TOP_SXRA_EXPIRED);

		successful_reset = (is_pl4_reset_finished && !is_pl4_outof_lock
				    && is_xaui_mabc_pll_locked);

		CH_DBG(adapter, HW,
		       "PM3393 HW reset %d: pl4_reset 0x%x, val 0x%x, "
		       "is_pl4_outof_lock 0x%x, xaui_locked 0x%x\n",
		       i, is_pl4_reset_finished, val, is_pl4_outof_lock,
		       is_xaui_mabc_pll_locked);
	}
	return successful_reset ? 0 : 1;
}