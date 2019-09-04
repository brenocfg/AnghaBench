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
 int PCIE_MMIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_MMIO_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCR ; 

__attribute__((used)) static int
pcie_mmio_uart_present( void )
{

    PCIE_MMIO_WRITE( SCR, 0x5a );
    if (PCIE_MMIO_READ(SCR) != 0x5a) return 0;
    PCIE_MMIO_WRITE( SCR, 0xa5 );
    if (PCIE_MMIO_READ(SCR) != 0xa5) return 0;

    return 1;
}