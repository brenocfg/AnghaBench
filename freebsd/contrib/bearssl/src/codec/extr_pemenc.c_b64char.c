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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static char
b64char(uint32_t x)
{
	/*
	 * Values 0 to 25 map to 0x41..0x5A ('A' to 'Z')
	 * Values 26 to 51 map to 0x61..0x7A ('a' to 'z')
	 * Values 52 to 61 map to 0x30..0x39 ('0' to '9')
	 * Value 62 maps to 0x2B ('+')
	 * Value 63 maps to 0x2F ('/')
	 */
	uint32_t a, b, c;

	a = x - 26;
	b = x - 52;
	c = x - 62;

	/*
	 * Looking at bits 8..15 of values a, b and c:
	 *
	 *     x       a   b   c
	 *  ---------------------
	 *   0..25    FF  FF  FF
	 *   26..51   00  FF  FF
	 *   52..61   00  00  FF
	 *   62..63   00  00  00
	 */
	return (char)(((x + 0x41) & ((a & b & c) >> 8))
		| ((x + (0x61 - 26)) & ((~a & b & c) >> 8))
		| ((x - (52 - 0x30)) & ((~a & ~b & c) >> 8))
		| ((0x2B + ((x & 1) << 2)) & (~(a | b | c) >> 8)));
}