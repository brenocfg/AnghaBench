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
struct conv {int noset; int set; scalar_t__ ctab; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct conv* bsearch (struct conv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_conv ; 
 int /*<<< orphan*/  clist ; 
 scalar_t__ ctab ; 
 int ddflags ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 

__attribute__((used)) static void
f_conv(char *arg)
{
	struct conv *cp, tmp;

	while (arg != NULL) {
		tmp.name = strsep(&arg, ",");
		cp = bsearch(&tmp, clist, nitems(clist), sizeof(struct conv),
		    c_conv);
		if (cp == NULL)
			errx(1, "unknown conversion %s", tmp.name);
		if (ddflags & cp->noset)
			errx(1, "%s: illegal conversion combination", tmp.name);
		ddflags |= cp->set;
		if (cp->ctab)
			ctab = cp->ctab;
	}
}