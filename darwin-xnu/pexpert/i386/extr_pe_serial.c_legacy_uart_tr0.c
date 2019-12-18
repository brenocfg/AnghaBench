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
 int IO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSR ; 
 int UART_LSR_THRE ; 

__attribute__((used)) static int
legacy_uart_tr0( void )
{
    return (IO_READ(LSR) & UART_LSR_THRE);
}