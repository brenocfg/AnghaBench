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
 int /*<<< orphan*/  DMERR (char*,char const*,int) ; 
 int /*<<< orphan*/  DMINFO (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static void init_exit(const char *bad_msg, const char *good_msg, int r)
{
	if (r)
		DMERR("Failed to %sregister target [%d]", bad_msg, r);
	else
		DMINFO("%s %s", good_msg, version);
}