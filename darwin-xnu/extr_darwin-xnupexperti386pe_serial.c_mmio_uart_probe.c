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
typedef  int /*<<< orphan*/  new_mmio_uart_base ;

/* Variables and functions */
 unsigned int MMIO_UART2_BASE ; 
 unsigned int MMIO_UART2_BASE_LEGACY ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 unsigned int mmio_uart_base ; 
 scalar_t__ mmio_uart_present () ; 

__attribute__((used)) static int
mmio_uart_probe( void )
{
    unsigned new_mmio_uart_base = 0;

    // if specified, mmio_uart overrides all probing
    if (PE_parse_boot_argn("mmio_uart", &new_mmio_uart_base, sizeof (new_mmio_uart_base)))
    {
        // mmio_uart=0 will disable mmio_uart support
        if (new_mmio_uart_base == 0) {
            return 0;
        }

        mmio_uart_base = new_mmio_uart_base;
        return 1;
    }

    // probe the two possible MMIO_UART2 addresses
    mmio_uart_base = MMIO_UART2_BASE;
    if (mmio_uart_present()) {
      return 1;
    }

    mmio_uart_base = MMIO_UART2_BASE_LEGACY;
    if (mmio_uart_present()) {
      return 1;
    }

    // no mmio uart found
    return 0;
}