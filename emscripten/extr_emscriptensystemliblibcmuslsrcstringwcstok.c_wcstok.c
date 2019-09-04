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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int wcscspn (scalar_t__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  wcsspn (scalar_t__*,scalar_t__ const*) ; 

wchar_t *wcstok(wchar_t *restrict s, const wchar_t *restrict sep, wchar_t **restrict p)
{
	if (!s && !(s = *p)) return NULL;
	s += wcsspn(s, sep);
	if (!*s) return *p = 0;
	*p = s + wcscspn(s, sep);
	if (**p) *(*p)++ = 0;
	else *p = 0;
	return s;
}