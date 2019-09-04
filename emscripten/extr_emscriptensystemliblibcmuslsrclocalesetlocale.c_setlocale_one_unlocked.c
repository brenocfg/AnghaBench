#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  struct __locale_map {scalar_t__ name; } const __locale_map ;
struct TYPE_3__ {struct __locale_map const** cat; } ;
struct TYPE_4__ {TYPE_1__ global_locale; } ;

/* Variables and functions */
 struct __locale_map const* __get_locale (int,char const*) ; 
 TYPE_2__ libc ; 

__attribute__((used)) static char *setlocale_one_unlocked(int cat, const char *name)
{
	const struct __locale_map *lm;

	if (name) libc.global_locale.cat[cat] = lm = __get_locale(cat, name);
	else lm = libc.global_locale.cat[cat];

	return lm ? (char *)lm->name : "C";
}