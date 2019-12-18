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
struct TYPE_2__ {char* value; scalar_t__ name; } ;

/* Variables and functions */
 int MAX_ENTRY ; 
 TYPE_1__* adam2_env ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

char *prom_getenv(const char *name)
{
	int i;
	for (i = 0; (i < MAX_ENTRY) && adam2_env[i].name; i++)
		if (!strcmp(name, adam2_env[i].name))
			return adam2_env[i].value;

	return NULL;
}