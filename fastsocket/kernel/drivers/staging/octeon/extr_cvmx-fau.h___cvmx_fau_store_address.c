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

/* Variables and functions */
 int CVMX_ADD_IO_SEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_FAU_BITS_NOADD ; 
 int /*<<< orphan*/  CVMX_FAU_BITS_REGISTER ; 
 int /*<<< orphan*/  CVMX_FAU_LOAD_IO_ADDRESS ; 
 int cvmx_build_bits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline uint64_t __cvmx_fau_store_address(uint64_t noadd, uint64_t reg)
{
	return CVMX_ADD_IO_SEG(CVMX_FAU_LOAD_IO_ADDRESS) |
	       cvmx_build_bits(CVMX_FAU_BITS_NOADD, noadd) |
	       cvmx_build_bits(CVMX_FAU_BITS_REGISTER, reg);
}