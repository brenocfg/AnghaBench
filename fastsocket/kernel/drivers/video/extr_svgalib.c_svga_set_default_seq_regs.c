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

/* Variables and functions */
 int /*<<< orphan*/  VGA_SEQ_CHARACTER_MAP ; 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_MEMORY_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_PLANE_WRITE ; 
 int VGA_SR01_CHAR_CLK_8DOTS ; 
 int VGA_SR02_ALL_PLANES ; 
 int VGA_SR04_EXT_MEM ; 
 int VGA_SR04_SEQ_MODE ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void svga_set_default_seq_regs(void)
{
	/* Standard sequencer registers (SR01 - SR04), SR00 is not set */
	vga_wseq(NULL, VGA_SEQ_CLOCK_MODE, VGA_SR01_CHAR_CLK_8DOTS);
	vga_wseq(NULL, VGA_SEQ_PLANE_WRITE, VGA_SR02_ALL_PLANES);
	vga_wseq(NULL, VGA_SEQ_CHARACTER_MAP, 0x00);
/*	vga_wseq(NULL, VGA_SEQ_MEMORY_MODE, VGA_SR04_EXT_MEM | VGA_SR04_SEQ_MODE | VGA_SR04_CHN_4M); */
	vga_wseq(NULL, VGA_SEQ_MEMORY_MODE, VGA_SR04_EXT_MEM | VGA_SR04_SEQ_MODE);
}