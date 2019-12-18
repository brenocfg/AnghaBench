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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000e_phy_init_script_igp3(struct e1000_hw *hw)
{
	e_dbg("Running IGP 3 PHY init script\n");

	/* PHY init IGP 3 */
	/* Enable rise/fall, 10-mode work in class-A */
	e1e_wphy(hw, 0x2F5B, 0x9018);
	/* Remove all caps from Replica path filter */
	e1e_wphy(hw, 0x2F52, 0x0000);
	/* Bias trimming for ADC, AFE and Driver (Default) */
	e1e_wphy(hw, 0x2FB1, 0x8B24);
	/* Increase Hybrid poly bias */
	e1e_wphy(hw, 0x2FB2, 0xF8F0);
	/* Add 4% to Tx amplitude in Gig mode */
	e1e_wphy(hw, 0x2010, 0x10B0);
	/* Disable trimming (TTT) */
	e1e_wphy(hw, 0x2011, 0x0000);
	/* Poly DC correction to 94.6% + 2% for all channels */
	e1e_wphy(hw, 0x20DD, 0x249A);
	/* ABS DC correction to 95.9% */
	e1e_wphy(hw, 0x20DE, 0x00D3);
	/* BG temp curve trim */
	e1e_wphy(hw, 0x28B4, 0x04CE);
	/* Increasing ADC OPAMP stage 1 currents to max */
	e1e_wphy(hw, 0x2F70, 0x29E4);
	/* Force 1000 ( required for enabling PHY regs configuration) */
	e1e_wphy(hw, 0x0000, 0x0140);
	/* Set upd_freq to 6 */
	e1e_wphy(hw, 0x1F30, 0x1606);
	/* Disable NPDFE */
	e1e_wphy(hw, 0x1F31, 0xB814);
	/* Disable adaptive fixed FFE (Default) */
	e1e_wphy(hw, 0x1F35, 0x002A);
	/* Enable FFE hysteresis */
	e1e_wphy(hw, 0x1F3E, 0x0067);
	/* Fixed FFE for short cable lengths */
	e1e_wphy(hw, 0x1F54, 0x0065);
	/* Fixed FFE for medium cable lengths */
	e1e_wphy(hw, 0x1F55, 0x002A);
	/* Fixed FFE for long cable lengths */
	e1e_wphy(hw, 0x1F56, 0x002A);
	/* Enable Adaptive Clip Threshold */
	e1e_wphy(hw, 0x1F72, 0x3FB0);
	/* AHT reset limit to 1 */
	e1e_wphy(hw, 0x1F76, 0xC0FF);
	/* Set AHT master delay to 127 msec */
	e1e_wphy(hw, 0x1F77, 0x1DEC);
	/* Set scan bits for AHT */
	e1e_wphy(hw, 0x1F78, 0xF9EF);
	/* Set AHT Preset bits */
	e1e_wphy(hw, 0x1F79, 0x0210);
	/* Change integ_factor of channel A to 3 */
	e1e_wphy(hw, 0x1895, 0x0003);
	/* Change prop_factor of channels BCD to 8 */
	e1e_wphy(hw, 0x1796, 0x0008);
	/* Change cg_icount + enable integbp for channels BCD */
	e1e_wphy(hw, 0x1798, 0xD008);
	/* Change cg_icount + enable integbp + change prop_factor_master
	 * to 8 for channel A
	 */
	e1e_wphy(hw, 0x1898, 0xD918);
	/* Disable AHT in Slave mode on channel A */
	e1e_wphy(hw, 0x187A, 0x0800);
	/* Enable LPLU and disable AN to 1000 in non-D0a states,
	 * Enable SPD+B2B
	 */
	e1e_wphy(hw, 0x0019, 0x008D);
	/* Enable restart AN on an1000_dis change */
	e1e_wphy(hw, 0x001B, 0x2080);
	/* Enable wh_fifo read clock in 10/100 modes */
	e1e_wphy(hw, 0x0014, 0x0045);
	/* Restart AN, Speed selection is 1000 */
	e1e_wphy(hw, 0x0000, 0x1340);

	return 0;
}