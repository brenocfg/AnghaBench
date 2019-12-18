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
struct dso {int long_name_len; int short_name_len; } ;

/* Variables and functions */
 int strlen (char*) ; 
 scalar_t__ verbose ; 

int dso__name_len(const struct dso *dso)
{
	if (!dso)
		return strlen("[unknown]");
	if (verbose)
		return dso->long_name_len;

	return dso->short_name_len;
}