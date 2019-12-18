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
typedef  int uint8_t ;

/* Variables and functions */
 int REX_W ; 
 scalar_t__ opcode_is_prefix (int const) ; 
 scalar_t__ opcode_is_rex_prefix (int const) ; 

void kmemcheck_opcode_decode(const uint8_t *op, unsigned int *size)
{
	/* Default operand size */
	int operand_size_override = 4;

	/* prefixes */
	for (; opcode_is_prefix(*op); ++op) {
		if (*op == 0x66)
			operand_size_override = 2;
	}

	/* REX prefix */
	if (opcode_is_rex_prefix(*op)) {
		uint8_t rex = *op;

		++op;
		if (rex & REX_W) {
			switch (*op) {
			case 0x63:
				*size = 4;
				return;
			case 0x0f:
				++op;

				switch (*op) {
				case 0xb6:
				case 0xbe:
					*size = 1;
					return;
				case 0xb7:
				case 0xbf:
					*size = 2;
					return;
				}

				break;
			}

			*size = 8;
			return;
		}
	}

	/* escape opcode */
	if (*op == 0x0f) {
		++op;

		/*
		 * This is move with zero-extend and sign-extend, respectively;
		 * we don't have to think about 0xb6/0xbe, because this is
		 * already handled in the conditional below.
		 */
		if (*op == 0xb7 || *op == 0xbf)
			operand_size_override = 2;
	}

	*size = (*op & 1) ? operand_size_override : 1;
}