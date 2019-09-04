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
 scalar_t__ wcschr (scalar_t__ const*,scalar_t__ const) ; 

size_t wcsspn(const wchar_t *s, const wchar_t *c)
{
	const wchar_t *a;
	for (a=s; *s && wcschr(c, *s); s++);
	return s-a;
}