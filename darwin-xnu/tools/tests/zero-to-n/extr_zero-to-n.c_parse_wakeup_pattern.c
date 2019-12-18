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
typedef  int /*<<< orphan*/  wake_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  WAKE_BROADCAST_ONESEM ; 
 int /*<<< orphan*/  WAKE_BROADCAST_PERTHREAD ; 
 int /*<<< orphan*/  WAKE_CHAIN ; 
 int /*<<< orphan*/  WAKE_HOP ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static wake_type_t
parse_wakeup_pattern(const char *str) 
{
	if (strcmp(str, "chain") == 0) {
		return WAKE_CHAIN;
	} else if (strcmp(str, "hop") == 0) {
		return WAKE_HOP;
	} else if (strcmp(str, "broadcast-single-sem") == 0) {
		return WAKE_BROADCAST_ONESEM;
	} else if (strcmp(str, "broadcast-per-thread") == 0) {
		return WAKE_BROADCAST_PERTHREAD;
	} else {
		errx(EX_USAGE, "Invalid wakeup pattern \"%s\"", str);
	}
}