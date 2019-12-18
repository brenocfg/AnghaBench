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
 int /*<<< orphan*/  m68328_console_initted ; 
 int /*<<< orphan*/  m68328_set_baud () ; 
 int /*<<< orphan*/  rs_put_char (char) ; 

void m68328_console_write (struct console *co, const char *str,
			   unsigned int count)
{
	if (!m68328_console_initted)
		m68328_set_baud();
    while (count--) {
        if (*str == '\n')
           rs_put_char('\r');
        rs_put_char( *str++ );
    }
}