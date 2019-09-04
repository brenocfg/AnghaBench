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
struct __locale_struct {struct __locale_map const** cat; } ;
struct __locale_map {int dummy; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_7__ {struct __locale_map** cat; } ;

/* Variables and functions */
 TYPE_1__* C_LOCALE ; 
 int LC_ALL ; 
 size_t LC_CTYPE ; 
 TYPE_1__* UTF8_LOCALE ; 
 struct __locale_map const __c_dot_utf8 ; 
 void* __get_locale (int,char const*) ; 
 scalar_t__ __loc_is_allocated (TYPE_1__*) ; 

locale_t __newlocale(int mask, const char *name, locale_t loc)
{
	int i, j;
	struct __locale_struct tmp;
	const struct __locale_map *lm;

	/* For locales with allocated storage, modify in-place. */
	if (__loc_is_allocated(loc)) {
		for (i=0; i<LC_ALL; i++)
			if (mask & (1<<i))
				loc->cat[i] = __get_locale(i, name);
		return loc;
	}

	/* Otherwise, build a temporary locale object, which will only
	 * be instantiated in allocated storage if it does not match
	 * one of the built-in static locales. This makes the common
	 * usage case for newlocale, getting a C locale with predictable
	 * behavior, very fast, and more importantly, fail-safe. */
	for (j=i=0; i<LC_ALL; i++) {
		if (loc && !(mask & (1<<i)))
			lm = loc->cat[i];
		else
			lm = __get_locale(i, mask & (1<<i) ? name : "");
		if (lm) j++;
		tmp.cat[i] = lm;
	}

	if (!j)
		return C_LOCALE;
	if (j==1 && tmp.cat[LC_CTYPE]==&__c_dot_utf8)
		return UTF8_LOCALE;

	return loc;
}