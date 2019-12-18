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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__* bits_in_16bits ; 

__attribute__((used)) static uint32_t compute_bits(uint64_t m) {
	return (bits_in_16bits[m & 0xffff] + bits_in_16bits[(m >> 16) & 0xffff] +
			bits_in_16bits[(m >> 32) & 0xffff] + bits_in_16bits[(m >> 48) & 0xffff]);
}