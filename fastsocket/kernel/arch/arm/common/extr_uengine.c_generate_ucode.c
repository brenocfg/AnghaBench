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

/* Variables and functions */

__attribute__((used)) static void generate_ucode(u8 *ucode, u32 *gpr_a, u32 *gpr_b)
{
	int offset;
	int i;

	offset = 0;

	for (i = 0; i < 128; i++) {
		u8 b3;
		u8 b2;
		u8 b1;
		u8 b0;

		b3 = (gpr_a[i] >> 24) & 0xff;
		b2 = (gpr_a[i] >> 16) & 0xff;
		b1 = (gpr_a[i] >> 8) & 0xff;
		b0 = gpr_a[i] & 0xff;

		// immed[@ai, (b1 << 8) | b0]
		// 11110000 0000VVVV VVVV11VV VVVVVV00 1IIIIIII
		ucode[offset++] = 0xf0;
		ucode[offset++] = (b1 >> 4);
		ucode[offset++] = (b1 << 4) | 0x0c | (b0 >> 6);
		ucode[offset++] = (b0 << 2);
		ucode[offset++] = 0x80 | i;

		// immed_w1[@ai, (b3 << 8) | b2]
		// 11110100 0100VVVV VVVV11VV VVVVVV00 1IIIIIII
		ucode[offset++] = 0xf4;
		ucode[offset++] = 0x40 | (b3 >> 4);
		ucode[offset++] = (b3 << 4) | 0x0c | (b2 >> 6);
		ucode[offset++] = (b2 << 2);
		ucode[offset++] = 0x80 | i;
	}

	for (i = 0; i < 128; i++) {
		u8 b3;
		u8 b2;
		u8 b1;
		u8 b0;

		b3 = (gpr_b[i] >> 24) & 0xff;
		b2 = (gpr_b[i] >> 16) & 0xff;
		b1 = (gpr_b[i] >> 8) & 0xff;
		b0 = gpr_b[i] & 0xff;

		// immed[@bi, (b1 << 8) | b0]
		// 11110000 0000VVVV VVVV001I IIIIII11 VVVVVVVV
		ucode[offset++] = 0xf0;
		ucode[offset++] = (b1 >> 4);
		ucode[offset++] = (b1 << 4) | 0x02 | (i >> 6);
		ucode[offset++] = (i << 2) | 0x03;
		ucode[offset++] = b0;

		// immed_w1[@bi, (b3 << 8) | b2]
		// 11110100 0100VVVV VVVV001I IIIIII11 VVVVVVVV
		ucode[offset++] = 0xf4;
		ucode[offset++] = 0x40 | (b3 >> 4);
		ucode[offset++] = (b3 << 4) | 0x02 | (i >> 6);
		ucode[offset++] = (i << 2) | 0x03;
		ucode[offset++] = b2;
	}

	// ctx_arb[kill]
	ucode[offset++] = 0xe0;
	ucode[offset++] = 0x00;
	ucode[offset++] = 0x01;
	ucode[offset++] = 0x00;
	ucode[offset++] = 0x00;
}