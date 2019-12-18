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
 int /*<<< orphan*/  uart_putc (char) ; 

__attribute__((used)) static void uart_puthex(uint64_t num)
{
    int bit;
    char c;
    bool leading = true;

    for (bit = 60; bit >= 0; bit -= 4)
    {
	c = 0xf & (num >> bit);
	if (c)
	    leading = false;
	else if (leading && bit)
	    continue;
	if (c <= 9)
	    c += '0';
	else
	    c+= 'a' - 10;
	uart_putc(c);
    }
}