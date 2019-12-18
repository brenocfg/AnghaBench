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
 int PEOF ; 
 int /*<<< orphan*/  doprompt ; 
 int /*<<< orphan*/  needprompt ; 
 int pgetc () ; 
 int /*<<< orphan*/  plinno ; 
 int /*<<< orphan*/  pungetc () ; 
 int /*<<< orphan*/  pushstring (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
checkend(int c, const char *eofmark, int striptabs)
{
	if (striptabs) {
		while (c == '\t')
			c = pgetc();
	}
	if (c == *eofmark) {
		int c2;
		const char *q;

		for (q = eofmark + 1; c2 = pgetc(), *q != '\0' && c2 == *q; q++)
			;
		if ((c2 == PEOF || c2 == '\n') && *q == '\0') {
			c = PEOF;
			if (c2 == '\n') {
				plinno++;
				needprompt = doprompt;
			}
		} else {
			pungetc();
			pushstring(eofmark + 1, q - (eofmark + 1), NULL);
		}
	} else if (c == '\n' && *eofmark == '\0') {
		c = PEOF;
		plinno++;
		needprompt = doprompt;
	}
	return (c);
}