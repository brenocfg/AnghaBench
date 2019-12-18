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
 int MS_SYNCHRONOUS ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  ubifs_msg (char*,char const*) ; 

__attribute__((used)) static int parse_standard_option(const char *option)
{
	ubifs_msg("parse %s", option);
	if (!strcmp(option, "sync"))
		return MS_SYNCHRONOUS;
	return 0;
}