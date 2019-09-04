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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_7__ {int /*<<< orphan*/  locale; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 size_t __fwritex (unsigned char*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  fwide (TYPE_1__*,int) ; 
 size_t wcsrtombs (void*,void*,int,int /*<<< orphan*/ ) ; 

int fputws(const wchar_t *restrict ws, FILE *restrict f)
{
	unsigned char buf[BUFSIZ];
	size_t l=0;
	locale_t *ploc = &CURRENT_LOCALE, loc = *ploc;

	FLOCK(f);

	fwide(f, 1);
	*ploc = f->locale;

	while (ws && (l = wcsrtombs((void *)buf, (void*)&ws, sizeof buf, 0))+1 > 1)
		if (__fwritex(buf, l, f) < l) {
			FUNLOCK(f);
			*ploc = loc;
			return -1;
		}

	FUNLOCK(f);

	*ploc = loc;
	return l; /* 0 or -1 */
}