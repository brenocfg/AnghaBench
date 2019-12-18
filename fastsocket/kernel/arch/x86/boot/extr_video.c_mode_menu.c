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
 unsigned int SCAN ; 
 unsigned int VIDEO_CURRENT_MODE ; 
 int /*<<< orphan*/  display_menu () ; 
 unsigned int get_entry () ; 
 int getchar_timeout () ; 
 int /*<<< orphan*/  kbd_flush () ; 
 int /*<<< orphan*/  probe_cards (int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static unsigned int mode_menu(void)
{
	int key;
	unsigned int sel;

	puts("Press <ENTER> to see video modes available, "
	     "<SPACE> to continue, or wait 30 sec\n");

	kbd_flush();
	while (1) {
		key = getchar_timeout();
		if (key == ' ' || key == 0)
			return VIDEO_CURRENT_MODE; /* Default */
		if (key == '\r')
			break;
		putchar('\a');	/* Beep! */
	}


	for (;;) {
		display_menu();

		puts("Enter a video mode or \"scan\" to scan for "
		     "additional modes: ");
		sel = get_entry();
		if (sel != SCAN)
			return sel;

		probe_cards(1);
	}
}