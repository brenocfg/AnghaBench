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

/* Variables and functions */
 int /*<<< orphan*/ * dac_regs ; 
 int vga_rseq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void ark_dac_write_regs(void *data, u8 *code, int count)
{
	u8 regval = vga_rseq(NULL, 0x1C);

	while (count != 0)
	{
		vga_wseq(NULL, 0x1C, regval | (code[0] & 4 ? 0x80 : 0));
		vga_w(NULL, dac_regs[code[0] & 3], code[1]);
		count--;
		code += 2;
	}

	vga_wseq(NULL, 0x1C, regval);
}