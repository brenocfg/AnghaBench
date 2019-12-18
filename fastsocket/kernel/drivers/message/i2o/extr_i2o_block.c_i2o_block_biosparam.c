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
 unsigned long BLOCK_SIZE_1G ; 
 unsigned long BLOCK_SIZE_21G ; 
 unsigned long BLOCK_SIZE_42G ; 
 unsigned long BLOCK_SIZE_528M ; 

__attribute__((used)) static void i2o_block_biosparam(unsigned long capacity, unsigned short *cyls,
				unsigned char *hds, unsigned char *secs)
{
	unsigned long heads, sectors, cylinders;

	sectors = 63L;		/* Maximize sectors per track */
	if (capacity <= BLOCK_SIZE_528M)
		heads = 16;
	else if (capacity <= BLOCK_SIZE_1G)
		heads = 32;
	else if (capacity <= BLOCK_SIZE_21G)
		heads = 64;
	else if (capacity <= BLOCK_SIZE_42G)
		heads = 128;
	else
		heads = 255;

	cylinders = (unsigned long)capacity / (heads * sectors);

	*cyls = (unsigned short)cylinders;	/* Stuff return values */
	*secs = (unsigned char)sectors;
	*hds = (unsigned char)heads;
}