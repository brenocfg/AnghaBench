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
struct savagefb_par {scalar_t__ chip; } ;
struct savage_reg {int SR08; int CR31; int CR32; int CR34; int CR36; int CR3A; int CR40; int CR42; int CR45; int CR50; int CR51; int CR53; int CR58; int CR60; int CR66; int CR67; int CR68; int CR69; int CR6F; int CR33; int CR86; int CR88; int CR90; int CR91; int CRB0; int CR3B; int CR3C; int CR43; int CR5D; int CR5E; int CR65; int SR0E; int SR0F; int SR10; int SR11; int SR12; int SR13; int SR29; int SR15; int SR30; int SR18; int* SR54; void* MMPR3; void* MMPR2; void* MMPR1; void* MMPR0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_CONTROL_REG ; 
 int /*<<< orphan*/  MISC_TIMEOUT_REG ; 
 int /*<<< orphan*/  MIU_CONTROL_REG ; 
 scalar_t__ S3_SAVAGE_MX ; 
 int /*<<< orphan*/  STREAMS_TIMEOUT_REG ; 
 void* savage_in32 (int /*<<< orphan*/ ,struct savagefb_par*) ; 
 int vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out16 (int,int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,unsigned char,struct savagefb_par*) ; 

__attribute__((used)) static void savage_get_default_par(struct savagefb_par *par, struct savage_reg *reg)
{
	unsigned char cr3a, cr53, cr66;

	vga_out16(0x3d4, 0x4838, par);
	vga_out16(0x3d4, 0xa039, par);
	vga_out16(0x3c4, 0x0608, par);

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);
	vga_out8(0x3d4, 0x53, par);
	cr53 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr53 & 0x7f, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	/* unlock extended seq regs */
	vga_out8(0x3c4, 0x08, par);
	reg->SR08 = vga_in8(0x3c5, par);
	vga_out8(0x3c5, 0x06, par);

	/* now save all the extended regs we need */
	vga_out8(0x3d4, 0x31, par);
	reg->CR31 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x32, par);
	reg->CR32 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x34, par);
	reg->CR34 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x36, par);
	reg->CR36 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x3a, par);
	reg->CR3A = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x40, par);
	reg->CR40 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x42, par);
	reg->CR42 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x45, par);
	reg->CR45 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x50, par);
	reg->CR50 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x51, par);
	reg->CR51 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x53, par);
	reg->CR53 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x58, par);
	reg->CR58 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x60, par);
	reg->CR60 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x66, par);
	reg->CR66 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x67, par);
	reg->CR67 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x68, par);
	reg->CR68 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x69, par);
	reg->CR69 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x6f, par);
	reg->CR6F = vga_in8(0x3d5, par);

	vga_out8(0x3d4, 0x33, par);
	reg->CR33 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x86, par);
	reg->CR86 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x88, par);
	reg->CR88 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x90, par);
	reg->CR90 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x91, par);
	reg->CR91 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0xb0, par);
	reg->CRB0 = vga_in8(0x3d5, par) | 0x80;

	/* extended mode timing regs */
	vga_out8(0x3d4, 0x3b, par);
	reg->CR3B = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x3c, par);
	reg->CR3C = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x43, par);
	reg->CR43 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x5d, par);
	reg->CR5D = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x5e, par);
	reg->CR5E = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x65, par);
	reg->CR65 = vga_in8(0x3d5, par);

	/* save seq extended regs for DCLK PLL programming */
	vga_out8(0x3c4, 0x0e, par);
	reg->SR0E = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x0f, par);
	reg->SR0F = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x10, par);
	reg->SR10 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x11, par);
	reg->SR11 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x12, par);
	reg->SR12 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x13, par);
	reg->SR13 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x29, par);
	reg->SR29 = vga_in8(0x3c5, par);

	vga_out8(0x3c4, 0x15, par);
	reg->SR15 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x30, par);
	reg->SR30 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x18, par);
	reg->SR18 = vga_in8(0x3c5, par);

	/* Save flat panel expansion regsters. */
	if (par->chip == S3_SAVAGE_MX) {
		int i;

		for (i = 0; i < 8; i++) {
			vga_out8(0x3c4, 0x54+i, par);
			reg->SR54[i] = vga_in8(0x3c5, par);
		}
	}

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);

	/* now save MIU regs */
	if (par->chip != S3_SAVAGE_MX) {
		reg->MMPR0 = savage_in32(FIFO_CONTROL_REG, par);
		reg->MMPR1 = savage_in32(MIU_CONTROL_REG, par);
		reg->MMPR2 = savage_in32(STREAMS_TIMEOUT_REG, par);
		reg->MMPR3 = savage_in32(MISC_TIMEOUT_REG, par);
	}

	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);
	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
}