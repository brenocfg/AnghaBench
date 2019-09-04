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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ * wmemchr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 

size_t wcsnlen(const wchar_t *s, size_t n)
{
	const wchar_t *z = wmemchr(s, 0, n);
	if (z) n = z-s;
	return n;
}