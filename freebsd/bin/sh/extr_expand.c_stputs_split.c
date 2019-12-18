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
struct worddest {int dummy; } ;

/* Variables and functions */
 char const CCTL ; 
 int /*<<< orphan*/  CHECKSTRSPACE (int,char*) ; 
 char CTLESC ; 
 int EXP_GLOB ; 
 int /*<<< orphan*/  NEXTWORD (char,int,char*,struct worddest*) ; 
 int /*<<< orphan*/  USTPUTC (char,char*) ; 
 scalar_t__ ifsset () ; 
 char* ifsval () ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static char *
stputs_split(const char *data, const char *syntax, int flag, char *p,
    struct worddest *dst)
{
	const char *ifs;
	char c;

	ifs = ifsset() ? ifsval() : " \t\n";
	while (*data) {
		CHECKSTRSPACE(2, p);
		c = *data++;
		if (strchr(ifs, c) != NULL) {
			NEXTWORD(c, flag, p, dst);
			continue;
		}
		if (flag & EXP_GLOB && syntax[(int)c] == CCTL)
			USTPUTC(CTLESC, p);
		USTPUTC(c, p);
	}
	return (p);
}