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
 unsigned int ioconfig_bitshift (unsigned int) ; 

__attribute__((used)) static inline unsigned pfi_output_select_bits(unsigned pfi_channel,
					      unsigned output_select)
{
	return (output_select & 0x3) << ioconfig_bitshift(pfi_channel);
}