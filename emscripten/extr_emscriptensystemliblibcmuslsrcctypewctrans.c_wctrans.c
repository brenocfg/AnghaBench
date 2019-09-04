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
typedef  int /*<<< orphan*/  wctrans_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

wctrans_t wctrans(const char *class)
{
	if (!strcmp(class, "toupper")) return (wctrans_t)1;
	if (!strcmp(class, "tolower")) return (wctrans_t)2;
	return 0;
}