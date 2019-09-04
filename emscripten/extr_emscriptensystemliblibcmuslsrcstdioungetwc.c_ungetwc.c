#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_7__ {scalar_t__ mode; int /*<<< orphan*/  flags; int /*<<< orphan*/ * rpos; int /*<<< orphan*/ * buf; int /*<<< orphan*/  locale; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  F_EOF ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/ * UNGET ; 
 int /*<<< orphan*/  WEOF ; 
 int /*<<< orphan*/  __toread (TYPE_1__*) ; 
 int /*<<< orphan*/  fwide (TYPE_1__*,int) ; 
 scalar_t__ isascii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int wcrtomb (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

wint_t ungetwc(wint_t c, FILE *f)
{
	unsigned char mbc[MB_LEN_MAX];
	int l;
	locale_t *ploc = &CURRENT_LOCALE, loc = *ploc;

	FLOCK(f);

	if (f->mode <= 0) fwide(f, 1);
	*ploc = f->locale;

	if (!f->rpos) __toread(f);
	if (!f->rpos || c == WEOF || (l = wcrtomb((void *)mbc, c, 0)) < 0 ||
	    f->rpos < f->buf - UNGET + l) {
		FUNLOCK(f);
		*ploc = loc;
		return WEOF;
	}

	if (isascii(c)) *--f->rpos = c;
	else memcpy(f->rpos -= l, mbc, l);

	f->flags &= ~F_EOF;

	FUNLOCK(f);
	*ploc = loc;
	return c;
}