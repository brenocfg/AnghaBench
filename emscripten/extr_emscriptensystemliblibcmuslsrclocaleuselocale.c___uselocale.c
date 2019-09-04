#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
typedef  scalar_t__ locale_t ;
struct TYPE_5__ {int /*<<< orphan*/  global_locale; } ;
struct TYPE_4__ {scalar_t__ locale; } ;

/* Variables and functions */
 scalar_t__ LC_GLOBAL_LOCALE ; 
 TYPE_1__* __pthread_self () ; 
 TYPE_2__ libc ; 

locale_t __uselocale(locale_t new)
{
	pthread_t self = __pthread_self();
	locale_t old = self->locale;
	locale_t global = &libc.global_locale;

	if (new) self->locale = new == LC_GLOBAL_LOCALE ? global : new;

	return old == global ? LC_GLOBAL_LOCALE : old;
}