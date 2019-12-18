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
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_spi_is_spi_interface(int interface)
{
	uint64_t gmxState = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));
	return (gmxState & 0x2) && (gmxState & 0x1);
}