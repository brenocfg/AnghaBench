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
 scalar_t__ doprompt ; 
 int pgetc () ; 
 int pgetc_macro () ; 
 int /*<<< orphan*/  plinno ; 
 int /*<<< orphan*/  pungetc () ; 
 int /*<<< orphan*/  pushstring (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprompt (int) ; 

__attribute__((used)) static int
pgetc_linecont(void)
{
	int c;

	while ((c = pgetc_macro()) == '\\') {
		c = pgetc();
		if (c == '\n') {
			plinno++;
			if (doprompt)
				setprompt(2);
			else
				setprompt(0);
		} else {
			pungetc();
			/* Allow the backslash to be pushed back. */
			pushstring("\\", 1, NULL);
			return (pgetc());
		}
	}
	return (c);
}