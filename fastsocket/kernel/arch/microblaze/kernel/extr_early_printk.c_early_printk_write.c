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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  early_printk_putc (char const) ; 

__attribute__((used)) static void early_printk_write(struct console *unused,
					const char *s, unsigned n)
{
	while (*s && n-- > 0) {
		early_printk_putc(*s);
		if (*s == '\n')
			early_printk_putc('\r');
		s++;
	}
}