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
 scalar_t__* BASESYNTAX ; 
 scalar_t__ CCTL ; 
 char const CTLESC ; 
 char const CTLQUOTEEND ; 
 char const CTLQUOTEMARK ; 

__attribute__((used)) static int
mustexpandto(const char *argtext, const char *mask)
{
	for (;;) {
		if (*argtext == CTLQUOTEMARK || *argtext == CTLQUOTEEND) {
			argtext++;
			continue;
		}
		if (*argtext == CTLESC)
			argtext++;
		else if (BASESYNTAX[(int)*argtext] == CCTL)
			return (0);
		if (*argtext != *mask)
			return (0);
		if (*argtext == '\0')
			return (1);
		argtext++;
		mask++;
	}
}