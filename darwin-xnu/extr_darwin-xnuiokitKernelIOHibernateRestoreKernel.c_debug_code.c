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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int gIOHibernateDebugFlags ; 
 int kIOHibernateDebugRestoreLogs ; 
 int /*<<< orphan*/  uart_putc (char) ; 
 int /*<<< orphan*/  uart_puthex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_code(uint32_t code, uint64_t value)
{
    int bit;
    char c;

    if (!(kIOHibernateDebugRestoreLogs & gIOHibernateDebugFlags))
	return;

    for (bit = 24; bit >= 0; bit -= 8)
    {
	c = 0xFF & (code >> bit);
	if (c)
	    uart_putc(c);
    }
    uart_putc('=');
    uart_puthex(value);
    uart_putc('\n');
    uart_putc('\r');
}