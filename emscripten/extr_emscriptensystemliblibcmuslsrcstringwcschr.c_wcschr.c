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
typedef  scalar_t__ const wchar_t ;

/* Variables and functions */
 int wcslen (scalar_t__ const*) ; 

wchar_t *wcschr(const wchar_t *s, wchar_t c)
{
	if (!c) return (wchar_t *)s + wcslen(s);
	for (; *s && *s != c; s++);
	return *s ? (wchar_t *)s : 0;
}