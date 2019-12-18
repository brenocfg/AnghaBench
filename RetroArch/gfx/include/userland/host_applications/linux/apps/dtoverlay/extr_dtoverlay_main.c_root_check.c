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
 int /*<<< orphan*/  cmd_name ; 
 int /*<<< orphan*/  fatal_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 

__attribute__((used)) static void root_check(void)
{
    if (getuid() != 0)
	fatal_error("Must be run as root - try 'sudo %s ...'", cmd_name);
}