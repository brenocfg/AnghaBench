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
 int DUMP_GROUPING ; 
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_ascii_block(char *subbuf, int length)
{
	int i;

	for (i = 0; i < length; i++) {
		char char_print = isprint(subbuf[i]) ? subbuf[i] : '.';
		if (i != 0 && i % DUMP_GROUPING == 0) {
			(void) printf(" ");
		}
		(void) printf("%c", char_print);
	}
	(void) printf("\n");
}