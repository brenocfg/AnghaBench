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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int calc_code_bit (unsigned int,unsigned int*) ; 
 unsigned int ocfs2_find_next_bit (void*,unsigned int,unsigned int) ; 

u32 ocfs2_hamming_encode(u32 parity, void *data, unsigned int d, unsigned int nr)
{
	unsigned int i, b, p = 0;

	BUG_ON(!d);

	/*
	 * b is the hamming code bit number.  Hamming code specifies a
	 * 1-based array, but C uses 0-based.  So 'i' is for C, and 'b' is
	 * for the algorithm.
	 *
	 * The i++ in the for loop is so that the start offset passed
	 * to ocfs2_find_next_bit_set() is one greater than the previously
	 * found bit.
	 */
	for (i = 0; (i = ocfs2_find_next_bit(data, d, i)) < d; i++)
	{
		/*
		 * i is the offset in this hunk, nr + i is the total bit
		 * offset.
		 */
		b = calc_code_bit(nr + i, &p);

		/*
		 * Data bits in the resultant code are checked by
		 * parity bits that are part of the bit number
		 * representation.  Huh?
		 *
		 * <wikipedia href="http://en.wikipedia.org/wiki/Hamming_code">
		 * In other words, the parity bit at position 2^k
		 * checks bits in positions having bit k set in
		 * their binary representation.  Conversely, for
		 * instance, bit 13, i.e. 1101(2), is checked by
		 * bits 1000(2) = 8, 0100(2)=4 and 0001(2) = 1.
		 * </wikipedia>
		 *
		 * Note that 'k' is the _code_ bit number.  'b' in
		 * our loop.
		 */
		parity ^= b;
	}

	/* While the data buffer was treated as little endian, the
	 * return value is in host endian. */
	return parity;
}