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

/* Variables and functions */
 char const* alias_key ; 
 int /*<<< orphan*/  alias_lookup_cb ; 
 char* alias_val ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

char *alias_lookup(const char *alias)
{
	alias_key = alias;
	alias_val = NULL;
	perf_config(alias_lookup_cb, NULL);
	return alias_val;
}