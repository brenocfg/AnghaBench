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
typedef  int /*<<< orphan*/  mach_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_EXPECT_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  T_EXPECT_NOTNULL (char const*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
expect_special_port_description(const char *(*fn)(mach_port_t),
		mach_port_t port, const char *namestr)
{
	const char *desc = fn(port);
	T_EXPECT_NOTNULL(desc, "%s is %s", namestr, desc);
	if (desc) {
		T_QUIET; T_EXPECT_GT(strlen(desc), strlen(""),
				"%s's description string is not empty", namestr);
	}
}