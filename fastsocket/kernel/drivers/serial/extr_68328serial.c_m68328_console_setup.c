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
 int BAUD_TABLE_SIZE ; 
 int CBAUDEX ; 
 int CONSOLE_BAUD_RATE ; 
 int* baud_table ; 
 int m68328_console_baud ; 
 int m68328_console_cbaud ; 
 int /*<<< orphan*/  m68328_set_baud () ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int m68328_console_setup(struct console *cp, char *arg)
{
	int		i, n = CONSOLE_BAUD_RATE;

	if (!cp)
		return(-1);

	if (arg)
		n = simple_strtoul(arg,NULL,0);

	for (i = 0; i < BAUD_TABLE_SIZE; i++)
		if (baud_table[i] == n)
			break;
	if (i < BAUD_TABLE_SIZE) {
		m68328_console_baud = n;
		m68328_console_cbaud = 0;
		if (i > 15) {
			m68328_console_cbaud |= CBAUDEX;
			i -= 15;
		}
		m68328_console_cbaud |= i;
	}

	m68328_set_baud(); /* make sure baud rate changes */
	return(0);
}