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
struct nodelist {int dummy; } ;

/* Variables and functions */
 int EXP_CASE ; 
 int EXP_TILDE ; 
 int /*<<< orphan*/  STACKSTRNUL (char*) ; 
 int /*<<< orphan*/  STADJUST (int,char*) ; 
#define  VSTRIMLEFT 131 
#define  VSTRIMLEFTMAX 130 
#define  VSTRIMRIGHT 129 
#define  VSTRIMRIGHTMAX 128 
 int /*<<< orphan*/  abort () ; 
 char* argstr (char const*,struct nodelist**,int,int /*<<< orphan*/ *) ; 
 char* expdest ; 
 int /*<<< orphan*/  patmatch (char*,char*) ; 
 int /*<<< orphan*/  recordleft (char*,char*,char*) ; 
 char* stackblock () ; 

__attribute__((used)) static const char *
subevalvar_trim(const char *p, struct nodelist **restrict argbackq, int strloc,
    int subtype, int startloc)
{
	char *startp;
	char *loc = NULL;
	char *str;
	int c = 0;
	int amount;

	p = argstr(p, argbackq, EXP_CASE | EXP_TILDE, NULL);
	STACKSTRNUL(expdest);
	startp = stackblock() + startloc;
	str = stackblock() + strloc;

	switch (subtype) {
	case VSTRIMLEFT:
		for (loc = startp; loc < str; loc++) {
			c = *loc;
			*loc = '\0';
			if (patmatch(str, startp)) {
				*loc = c;
				recordleft(str, loc, startp);
				return p;
			}
			*loc = c;
		}
		break;

	case VSTRIMLEFTMAX:
		for (loc = str - 1; loc >= startp;) {
			c = *loc;
			*loc = '\0';
			if (patmatch(str, startp)) {
				*loc = c;
				recordleft(str, loc, startp);
				return p;
			}
			*loc = c;
			loc--;
		}
		break;

	case VSTRIMRIGHT:
		for (loc = str - 1; loc >= startp;) {
			if (patmatch(str, loc)) {
				amount = loc - expdest;
				STADJUST(amount, expdest);
				return p;
			}
			loc--;
		}
		break;

	case VSTRIMRIGHTMAX:
		for (loc = startp; loc < str - 1; loc++) {
			if (patmatch(str, loc)) {
				amount = loc - expdest;
				STADJUST(amount, expdest);
				return p;
			}
		}
		break;


	default:
		abort();
	}
	amount = (expdest - stackblock() - strloc) + 1;
	STADJUST(-amount, expdest);
	return p;
}