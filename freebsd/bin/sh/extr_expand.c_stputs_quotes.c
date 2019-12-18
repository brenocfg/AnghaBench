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
 char const CCTL ; 
 int /*<<< orphan*/  CHECKSTRSPACE (int,char*) ; 
 int /*<<< orphan*/  CTLESC ; 
 int /*<<< orphan*/  USTPUTC (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
stputs_quotes(const char *data, const char *syntax, char *p)
{
	while (*data) {
		CHECKSTRSPACE(2, p);
		if (syntax[(int)*data] == CCTL)
			USTPUTC(CTLESC, p);
		USTPUTC(*data++, p);
	}
	return (p);
}