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
struct console {int flags; struct console* next; } ;

/* Variables and functions */
 int CON_BRL ; 
 int CON_CONSDEV ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int braille_unregister_console (struct console*) ; 
 struct console* console_drivers ; 
 int /*<<< orphan*/  release_console_sem () ; 

int unregister_console(struct console *console)
{
        struct console *a, *b;
	int res = 1;

#ifdef CONFIG_A11Y_BRAILLE_CONSOLE
	if (console->flags & CON_BRL)
		return braille_unregister_console(console);
#endif

	acquire_console_sem();
	if (console_drivers == console) {
		console_drivers=console->next;
		res = 0;
	} else if (console_drivers) {
		for (a=console_drivers->next, b=console_drivers ;
		     a; b=a, a=b->next) {
			if (a == console) {
				b->next = a->next;
				res = 0;
				break;
			}
		}
	}

	/*
	 * If this isn't the last console and it has CON_CONSDEV set, we
	 * need to set it on the next preferred console.
	 */
	if (console_drivers != NULL && console->flags & CON_CONSDEV)
		console_drivers->flags |= CON_CONSDEV;

	release_console_sem();
	return res;
}