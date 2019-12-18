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
typedef  void* uint64_t ;

/* Variables and functions */
 size_t MAX_BIT_FILTERS ; 
 int /*<<< orphan*/  fatal (char*) ; 
 size_t nr_bit_filters ; 
 void** opt_bits ; 
 void** opt_mask ; 

__attribute__((used)) static void add_bits_filter(uint64_t mask, uint64_t bits)
{
	if (nr_bit_filters >= MAX_BIT_FILTERS)
		fatal("too much bit filters\n");

	opt_mask[nr_bit_filters] = mask;
	opt_bits[nr_bit_filters] = bits;
	nr_bit_filters++;
}