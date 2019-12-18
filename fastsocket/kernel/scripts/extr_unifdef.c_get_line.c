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
typedef  scalar_t__ Linetype ;
typedef  int Comment_state ;

/* Variables and functions */
 int /*<<< orphan*/  Eioccc () ; 
 size_t LS_DIRTY ; 
 size_t LS_HASH ; 
 size_t LS_START ; 
 scalar_t__ LT_DODGY ; 
 scalar_t__ LT_ELFALSE ; 
 scalar_t__ LT_ELIF ; 
 scalar_t__ LT_ELSE ; 
 scalar_t__ LT_ELTRUE ; 
 scalar_t__ LT_ENDIF ; 
 scalar_t__ LT_EOF ; 
 scalar_t__ LT_FALSE ; 
 scalar_t__ LT_FALSEI ; 
 scalar_t__ LT_IF ; 
 scalar_t__ LT_PLAIN ; 
 scalar_t__ LT_TRUE ; 
 scalar_t__ LT_TRUEI ; 
 int /*<<< orphan*/  MAXLINE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * comment_name ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int findsym (char const*) ; 
 scalar_t__ ifeval (char const**) ; 
 scalar_t__* ignore ; 
 int incomment ; 
 int /*<<< orphan*/  input ; 
 char const* keyword ; 
 size_t linestate ; 
 int /*<<< orphan*/ * linestate_name ; 
 char* skipcomment (char const*) ; 
 char* skipsym (char const*) ; 
 scalar_t__ strlcmp (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char const* tline ; 
 int /*<<< orphan*/ ** value ; 

__attribute__((used)) static Linetype
get_line(void)
{
	const char *cp;
	int cursym;
	int kwlen;
	Linetype retval;
	Comment_state wascomment;

	if (fgets(tline, MAXLINE, input) == NULL)
		return (LT_EOF);
	retval = LT_PLAIN;
	wascomment = incomment;
	cp = skipcomment(tline);
	if (linestate == LS_START) {
		if (*cp == '#') {
			linestate = LS_HASH;
			cp = skipcomment(cp + 1);
		} else if (*cp != '\0')
			linestate = LS_DIRTY;
	}
	if (!incomment && linestate == LS_HASH) {
		keyword = tline + (cp - tline);
		cp = skipsym(cp);
		kwlen = cp - keyword;
		/* no way can we deal with a continuation inside a keyword */
		if (strncmp(cp, "\\\n", 2) == 0)
			Eioccc();
		if (strlcmp("ifdef", keyword, kwlen) == 0 ||
		    strlcmp("ifndef", keyword, kwlen) == 0) {
			cp = skipcomment(cp);
			if ((cursym = findsym(cp)) < 0)
				retval = LT_IF;
			else {
				retval = (keyword[2] == 'n')
				    ? LT_FALSE : LT_TRUE;
				if (value[cursym] == NULL)
					retval = (retval == LT_TRUE)
					    ? LT_FALSE : LT_TRUE;
				if (ignore[cursym])
					retval = (retval == LT_TRUE)
					    ? LT_TRUEI : LT_FALSEI;
			}
			cp = skipsym(cp);
		} else if (strlcmp("if", keyword, kwlen) == 0)
			retval = ifeval(&cp);
		else if (strlcmp("elif", keyword, kwlen) == 0)
			retval = ifeval(&cp) - LT_IF + LT_ELIF;
		else if (strlcmp("else", keyword, kwlen) == 0)
			retval = LT_ELSE;
		else if (strlcmp("endif", keyword, kwlen) == 0)
			retval = LT_ENDIF;
		else {
			linestate = LS_DIRTY;
			retval = LT_PLAIN;
		}
		cp = skipcomment(cp);
		if (*cp != '\0') {
			linestate = LS_DIRTY;
			if (retval == LT_TRUE || retval == LT_FALSE ||
			    retval == LT_TRUEI || retval == LT_FALSEI)
				retval = LT_IF;
			if (retval == LT_ELTRUE || retval == LT_ELFALSE)
				retval = LT_ELIF;
		}
		if (retval != LT_PLAIN && (wascomment || incomment)) {
			retval += LT_DODGY;
			if (incomment)
				linestate = LS_DIRTY;
		}
		/* skipcomment should have changed the state */
		if (linestate == LS_HASH)
			abort(); /* bug */
	}
	if (linestate == LS_DIRTY) {
		while (*cp != '\0')
			cp = skipcomment(cp + 1);
	}
	debug("parser %s comment %s line",
	    comment_name[incomment], linestate_name[linestate]);
	return (retval);
}