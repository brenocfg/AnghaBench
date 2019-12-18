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
struct operand {int shift; int bits; int flags; } ;

/* Variables and functions */
 int OPERAND_LENGTH ; 
 int OPERAND_PCREL ; 
 int OPERAND_SIGNED ; 

__attribute__((used)) static unsigned int extract_operand(unsigned char *code,
				    const struct operand *operand)
{
	unsigned int val;
	int bits;

	/* Extract fragments of the operand byte for byte.  */
	code += operand->shift / 8;
	bits = (operand->shift & 7) + operand->bits;
	val = 0;
	do {
		val <<= 8;
		val |= (unsigned int) *code++;
		bits -= 8;
	} while (bits > 0);
	val >>= -bits;
	val &= ((1U << (operand->bits - 1)) << 1) - 1;

	/* Check for special long displacement case.  */
	if (operand->bits == 20 && operand->shift == 20)
		val = (val & 0xff) << 12 | (val & 0xfff00) >> 8;

	/* Sign extend value if the operand is signed or pc relative.  */
	if ((operand->flags & (OPERAND_SIGNED | OPERAND_PCREL)) &&
	    (val & (1U << (operand->bits - 1))))
		val |= (-1U << (operand->bits - 1)) << 1;

	/* Double value if the operand is pc relative.	*/
	if (operand->flags & OPERAND_PCREL)
		val <<= 1;

	/* Length x in an instructions has real length x + 1.  */
	if (operand->flags & OPERAND_LENGTH)
		val++;
	return val;
}