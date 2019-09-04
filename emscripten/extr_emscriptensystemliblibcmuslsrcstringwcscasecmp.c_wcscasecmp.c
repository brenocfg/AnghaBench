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
 int wcsncasecmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int wcscasecmp(const wchar_t *l, const wchar_t *r)
{
	return wcsncasecmp(l, r, -1);
}