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
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void debug_test(void)
{
	err("This is an error.\n");
	warn("This is a warnig.\n");
	info("This is an informative message.\n");
	dbg("This is just utter useless babble.\n");
}