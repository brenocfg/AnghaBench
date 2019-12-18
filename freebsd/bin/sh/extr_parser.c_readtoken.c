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
struct alias {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int CHKALIAS ; 
 int CHKKWD ; 
 int CHKNL ; 
 int KWDOFFSET ; 
 int TNL ; 
 int TNOT ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TWORD ; 
 int checkkwd ; 
 scalar_t__ equal (char const* const,char const*) ; 
 int lasttoken ; 
 struct alias* lookupalias (char const*,int) ; 
 int /*<<< orphan*/  parseheredoc () ; 
 char const* const* parsekwd ; 
 int /*<<< orphan*/  pushstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct alias*) ; 
 int /*<<< orphan*/  quoteflag ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tokname ; 
 int tokpushback ; 
 char const* wordtext ; 
 int xxreadtoken () ; 

__attribute__((used)) static int
readtoken(void)
{
	int t;
	struct alias *ap;
#ifdef DEBUG
	int alreadyseen = tokpushback;
#endif

	top:
	t = xxreadtoken();

	/*
	 * eat newlines
	 */
	if (checkkwd & CHKNL) {
		while (t == TNL) {
			parseheredoc();
			t = xxreadtoken();
		}
	}

	/*
	 * check for keywords and aliases
	 */
	if (t == TWORD && !quoteflag)
	{
		const char * const *pp;

		if (checkkwd & CHKKWD)
			for (pp = parsekwd; *pp; pp++) {
				if (**pp == *wordtext && equal(*pp, wordtext))
				{
					lasttoken = t = pp - parsekwd + KWDOFFSET;
					TRACE(("keyword %s recognized\n", tokname[t]));
					goto out;
				}
			}
		if (checkkwd & CHKALIAS &&
		    (ap = lookupalias(wordtext, 1)) != NULL) {
			pushstring(ap->val, strlen(ap->val), ap);
			goto top;
		}
	}
out:
	if (t != TNOT)
		checkkwd = 0;

#ifdef DEBUG
	if (!alreadyseen)
	    TRACE(("token %s %s\n", tokname[t], t == TWORD ? wordtext : ""));
	else
	    TRACE(("reread token %s %s\n", tokname[t], t == TWORD ? wordtext : ""));
#endif
	return (t);
}