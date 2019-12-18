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
 int /*<<< orphan*/  color_parse_mem (char const*,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void color_parse(const char *value, const char *var, char *dst)
{
	color_parse_mem(value, strlen(value), var, dst);
}