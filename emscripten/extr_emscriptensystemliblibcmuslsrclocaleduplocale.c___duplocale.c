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
typedef  int /*<<< orphan*/ * locale_t ;
struct TYPE_2__ {int /*<<< orphan*/  global_locale; } ;

/* Variables and functions */
 int /*<<< orphan*/ * LC_GLOBAL_LOCALE ; 
 TYPE_1__ libc ; 
 int /*<<< orphan*/ * malloc (int) ; 

locale_t __duplocale(locale_t old)
{
	locale_t new = malloc(sizeof *new);
	if (!new) return 0;
	if (old == LC_GLOBAL_LOCALE) old = &libc.global_locale;
	*new = *old;
	return new;
}