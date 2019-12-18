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
struct dso {char* long_name; int /*<<< orphan*/  long_name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char*) ; 

void dso__set_long_name(struct dso *dso, char *name)
{
	if (name == NULL)
		return;
	dso->long_name = name;
	dso->long_name_len = strlen(name);
}