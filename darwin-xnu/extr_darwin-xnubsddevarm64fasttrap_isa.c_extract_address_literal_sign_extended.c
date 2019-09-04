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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int sign_extend (int,int) ; 

__attribute__((used)) static uint64_t
extract_address_literal_sign_extended(uint32_t instr, uint32_t base, uint32_t numbits)
{
	uint64_t offset;

	offset = (instr >> base) & ((1 << numbits) - 1);
	offset = sign_extend(offset, numbits - 1);
	offset = offset << 2;

	return offset;
}