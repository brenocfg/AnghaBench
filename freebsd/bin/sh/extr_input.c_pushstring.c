#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strpush {char const* prevstring; int prevnleft; struct alias* ap; int /*<<< orphan*/  prevlleft; struct strpush* prev; } ;
struct alias {int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {struct strpush basestrpush; struct strpush* strpush; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIASINUSE ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 struct strpush* ckmalloc (int) ; 
 TYPE_1__* parsefile ; 
 int /*<<< orphan*/  parselleft ; 
 char const* parsenextc ; 
 int parsenleft ; 

void
pushstring(const char *s, int len, struct alias *ap)
{
	struct strpush *sp;

	INTOFF;
/*out2fmt_flush("*** calling pushstring: %s, %d\n", s, len);*/
	if (parsefile->strpush) {
		sp = ckmalloc(sizeof (struct strpush));
		sp->prev = parsefile->strpush;
		parsefile->strpush = sp;
	} else
		sp = parsefile->strpush = &(parsefile->basestrpush);
	sp->prevstring = parsenextc;
	sp->prevnleft = parsenleft;
	sp->prevlleft = parselleft;
	sp->ap = ap;
	if (ap)
		ap->flag |= ALIASINUSE;
	parsenextc = s;
	parsenleft = len;
	INTON;
}