#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_5__ {scalar_t__ mode; int /*<<< orphan*/  locale; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 int /*<<< orphan*/  __fgetwc_unlocked_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  fwide (TYPE_1__*,int) ; 

wint_t __fgetwc_unlocked(FILE *f)
{
	locale_t *ploc = &CURRENT_LOCALE, loc = *ploc;
	if (f->mode <= 0) fwide(f, 1);
	*ploc = f->locale;
	wchar_t wc = __fgetwc_unlocked_internal(f);
	*ploc = loc;
	return wc;
}