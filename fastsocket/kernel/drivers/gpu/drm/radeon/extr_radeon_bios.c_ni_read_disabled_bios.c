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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVIVO_D1VGA_CONTROL ; 
 int /*<<< orphan*/  AVIVO_D2VGA_CONTROL ; 
 int AVIVO_DVGA_CONTROL_MODE_ENABLE ; 
 int AVIVO_DVGA_CONTROL_TIMING_SELECT ; 
 int /*<<< orphan*/  AVIVO_VGA_RENDER_CONTROL ; 
 int AVIVO_VGA_VSTATUS_CNTL_MASK ; 
 int R600_BIOS_ROM_DIS ; 
 int /*<<< orphan*/  R600_BUS_CNTL ; 
 int /*<<< orphan*/  R600_ROM_CNTL ; 
 int R600_SCK_OVERWRITE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int radeon_read_bios (struct radeon_device*) ; 

__attribute__((used)) static bool ni_read_disabled_bios(struct radeon_device *rdev)
{
	u32 bus_cntl;
	u32 d1vga_control;
	u32 d2vga_control;
	u32 vga_render_control;
	u32 rom_cntl;
	bool r;

	bus_cntl = RREG32(R600_BUS_CNTL);
	d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
	d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
	vga_render_control = RREG32(AVIVO_VGA_RENDER_CONTROL);
	rom_cntl = RREG32(R600_ROM_CNTL);

	/* enable the rom */
	WREG32(R600_BUS_CNTL, (bus_cntl & ~R600_BIOS_ROM_DIS));
	/* Disable VGA mode */
	WREG32(AVIVO_D1VGA_CONTROL,
	       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_D2VGA_CONTROL,
	       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_VGA_RENDER_CONTROL,
	       (vga_render_control & ~AVIVO_VGA_VSTATUS_CNTL_MASK));
	WREG32(R600_ROM_CNTL, rom_cntl | R600_SCK_OVERWRITE);

	r = radeon_read_bios(rdev);

	/* restore regs */
	WREG32(R600_BUS_CNTL, bus_cntl);
	WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
	WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
	WREG32(AVIVO_VGA_RENDER_CONTROL, vga_render_control);
	WREG32(R600_ROM_CNTL, rom_cntl);
	return r;
}