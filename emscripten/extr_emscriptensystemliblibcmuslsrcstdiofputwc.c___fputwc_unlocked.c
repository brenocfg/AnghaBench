#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_6__ {scalar_t__ mode; int wpos; int wend; int /*<<< orphan*/  flags; int /*<<< orphan*/  locale; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 int /*<<< orphan*/  F_ERR ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  WEOF ; 
 int __fwritex (void*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  fwide (TYPE_1__*,int) ; 
 scalar_t__ isascii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc_unlocked (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int wctomb (char*,int /*<<< orphan*/ ) ; 

wint_t __fputwc_unlocked(wchar_t c, FILE *f)
{
	char mbc[MB_LEN_MAX];
	int l;
	locale_t *ploc = &CURRENT_LOCALE, loc = *ploc;

	if (f->mode <= 0) fwide(f, 1);
	*ploc = f->locale;

	if (isascii(c)) {
		c = putc_unlocked(c, f);
	} else if (f->wpos + MB_LEN_MAX < f->wend) {
		l = wctomb((void *)f->wpos, c);
		if (l < 0) c = WEOF;
		else f->wpos += l;
	} else {
		l = wctomb(mbc, c);
		if (l < 0 || __fwritex((void *)mbc, l, f) < l) c = WEOF;
	}
	if (c==WEOF) f->flags |= F_ERR;
	*ploc = loc;
	return c;
}