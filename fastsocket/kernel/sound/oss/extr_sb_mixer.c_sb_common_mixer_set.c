#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int iomap_sz; TYPE_1__*** iomap; } ;
typedef  TYPE_2__ sb_devc ;
struct TYPE_7__ {int regno; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t LEFT_CHN ; 
 size_t RIGHT_CHN ; 
 int /*<<< orphan*/  change_bits (TYPE_2__*,unsigned char*,int,size_t,int) ; 
 unsigned char sb_getmixer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sb_setmixer (TYPE_2__*,int,unsigned char) ; 

int sb_common_mixer_set(sb_devc * devc, int dev, int left, int right)
{
	int regoffs;
	unsigned char val;

	if ((dev < 0) || (dev >= devc->iomap_sz))
		return -EINVAL;

	regoffs = (*devc->iomap)[dev][LEFT_CHN].regno;

	if (regoffs == 0)
		return -EINVAL;

	val = sb_getmixer(devc, regoffs);
	change_bits(devc, &val, dev, LEFT_CHN, left);

	if ((*devc->iomap)[dev][RIGHT_CHN].regno != regoffs)	/*
								 * Change register
								 */
	{
		sb_setmixer(devc, regoffs, val);	/*
							 * Save the old one
							 */
		regoffs = (*devc->iomap)[dev][RIGHT_CHN].regno;

		if (regoffs == 0)
			return left | (left << 8);	/*
							 * Just left channel present
							 */

		val = sb_getmixer(devc, regoffs);	/*
							 * Read the new one
							 */
	}
	change_bits(devc, &val, dev, RIGHT_CHN, right);

	sb_setmixer(devc, regoffs, val);

	return left | (right << 8);
}