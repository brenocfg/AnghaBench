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
struct omap_mcbsp {int /*<<< orphan*/  dev; int /*<<< orphan*/  io_base; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRR1 ; 
 int /*<<< orphan*/  DRR2 ; 
 int /*<<< orphan*/  DXR1 ; 
 int /*<<< orphan*/  DXR2 ; 
 int /*<<< orphan*/  OMAP_MCBSP_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR0 ; 
 int /*<<< orphan*/  RCR1 ; 
 int /*<<< orphan*/  RCR2 ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  SPCR2 ; 
 int /*<<< orphan*/  SRGR1 ; 
 int /*<<< orphan*/  SRGR2 ; 
 int /*<<< orphan*/  XCR1 ; 
 int /*<<< orphan*/  XCR2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct omap_mcbsp* id_to_mcbsp_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mcbsp_dump_reg(u8 id)
{
	struct omap_mcbsp *mcbsp = id_to_mcbsp_ptr(id);

	dev_dbg(mcbsp->dev, "**** McBSP%d regs ****\n", mcbsp->id);
	dev_dbg(mcbsp->dev, "DRR2:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, DRR2));
	dev_dbg(mcbsp->dev, "DRR1:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, DRR1));
	dev_dbg(mcbsp->dev, "DXR2:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, DXR2));
	dev_dbg(mcbsp->dev, "DXR1:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, DXR1));
	dev_dbg(mcbsp->dev, "SPCR2: 0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, SPCR2));
	dev_dbg(mcbsp->dev, "SPCR1: 0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, SPCR1));
	dev_dbg(mcbsp->dev, "RCR2:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, RCR2));
	dev_dbg(mcbsp->dev, "RCR1:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, RCR1));
	dev_dbg(mcbsp->dev, "XCR2:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, XCR2));
	dev_dbg(mcbsp->dev, "XCR1:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, XCR1));
	dev_dbg(mcbsp->dev, "SRGR2: 0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, SRGR2));
	dev_dbg(mcbsp->dev, "SRGR1: 0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, SRGR1));
	dev_dbg(mcbsp->dev, "PCR0:  0x%04x\n",
			OMAP_MCBSP_READ(mcbsp->io_base, PCR0));
	dev_dbg(mcbsp->dev, "***********************\n");
}