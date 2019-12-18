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
struct tridentfb_par {int /*<<< orphan*/  io_virt; int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NewMode1 ; 
 int PCIReg ; 
 int /*<<< orphan*/  Protection ; 
 int /*<<< orphan*/  is_oldprotect (int /*<<< orphan*/ ) ; 
 int t_inb (struct tridentfb_par*,int) ; 
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,int,int) ; 
 int /*<<< orphan*/  vga_mm_rseq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_mm_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_mmio(struct tridentfb_par *par)
{
	/* Goto New Mode */
	vga_mm_rseq(par->io_virt, 0x0B);

	/* Unprotect registers */
	vga_mm_wseq(par->io_virt, NewMode1, 0x80);
	if (!is_oldprotect(par->chip_id))
		vga_mm_wseq(par->io_virt, Protection, 0x92);

	/* Disable MMIO */
	t_outb(par, PCIReg, 0x3D4);
	t_outb(par, t_inb(par, 0x3D5) & ~0x01, 0x3D5);
}