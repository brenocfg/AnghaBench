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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ PCI_UART2 ; 
 scalar_t__ TRUE ; 
 int lpss_uart_enabled ; 
 int /*<<< orphan*/  lpss_uart_re_init () ; 
 int /*<<< orphan*/  lpss_uart_supported ; 
 unsigned int ml_phys_read_byte (scalar_t__) ; 
 int /*<<< orphan*/  ml_phys_write_byte (scalar_t__,unsigned int) ; 

void lpss_uart_enable( boolean_t on_off )
{
	unsigned int pmcs_reg;

	if (!lpss_uart_supported) {
		return;
	}

	pmcs_reg = ml_phys_read_byte (PCI_UART2 + 0x84);
	if (on_off == FALSE) {
		pmcs_reg |= 0x03;
		lpss_uart_enabled = 0;
	} else {
		pmcs_reg &= ~(0x03);
	}

	ml_phys_write_byte (PCI_UART2 + 0x84, pmcs_reg);
	pmcs_reg = ml_phys_read_byte (PCI_UART2 + 0x84);
	
	if (on_off == TRUE) {
		lpss_uart_re_init();
		lpss_uart_enabled = 1;
	}
}