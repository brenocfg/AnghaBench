#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t* blf_data_map; } ;
struct TYPE_6__ {TYPE_1__ bli_format; int /*<<< orphan*/  bli_flags; } ;
typedef  TYPE_2__ xfs_buf_log_item_t ;
typedef  size_t uint ;

/* Variables and functions */
 size_t BIT_TO_WORD_SHIFT ; 
 size_t MIN (size_t,size_t) ; 
 int NBWORD ; 
 size_t XFS_BLF_SHIFT ; 
 int /*<<< orphan*/  XFS_BLI_DIRTY ; 
 int /*<<< orphan*/  xfs_buf_item_log_debug (TYPE_2__*,size_t,size_t) ; 

void
xfs_buf_item_log(
	xfs_buf_log_item_t	*bip,
	uint			first,
	uint			last)
{
	uint		first_bit;
	uint		last_bit;
	uint		bits_to_set;
	uint		bits_set;
	uint		word_num;
	uint		*wordp;
	uint		bit;
	uint		end_bit;
	uint		mask;

	/*
	 * Mark the item as having some dirty data for
	 * quick reference in xfs_buf_item_dirty.
	 */
	bip->bli_flags |= XFS_BLI_DIRTY;

	/*
	 * Convert byte offsets to bit numbers.
	 */
	first_bit = first >> XFS_BLF_SHIFT;
	last_bit = last >> XFS_BLF_SHIFT;

	/*
	 * Calculate the total number of bits to be set.
	 */
	bits_to_set = last_bit - first_bit + 1;

	/*
	 * Get a pointer to the first word in the bitmap
	 * to set a bit in.
	 */
	word_num = first_bit >> BIT_TO_WORD_SHIFT;
	wordp = &(bip->bli_format.blf_data_map[word_num]);

	/*
	 * Calculate the starting bit in the first word.
	 */
	bit = first_bit & (uint)(NBWORD - 1);

	/*
	 * First set any bits in the first word of our range.
	 * If it starts at bit 0 of the word, it will be
	 * set below rather than here.  That is what the variable
	 * bit tells us. The variable bits_set tracks the number
	 * of bits that have been set so far.  End_bit is the number
	 * of the last bit to be set in this word plus one.
	 */
	if (bit) {
		end_bit = MIN(bit + bits_to_set, (uint)NBWORD);
		mask = ((1 << (end_bit - bit)) - 1) << bit;
		*wordp |= mask;
		wordp++;
		bits_set = end_bit - bit;
	} else {
		bits_set = 0;
	}

	/*
	 * Now set bits a whole word at a time that are between
	 * first_bit and last_bit.
	 */
	while ((bits_to_set - bits_set) >= NBWORD) {
		*wordp |= 0xffffffff;
		bits_set += NBWORD;
		wordp++;
	}

	/*
	 * Finally, set any bits left to be set in one last partial word.
	 */
	end_bit = bits_to_set - bits_set;
	if (end_bit) {
		mask = (1 << end_bit) - 1;
		*wordp |= mask;
	}

	xfs_buf_item_log_debug(bip, first, last);
}