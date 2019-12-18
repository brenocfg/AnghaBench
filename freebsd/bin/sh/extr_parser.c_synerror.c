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
 char const* arg0 ; 
 scalar_t__ commandname ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  outfmt (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  startlinno ; 

__attribute__((used)) static void
synerror(const char *msg)
{
	if (commandname)
		outfmt(out2, "%s: %d: ", commandname, startlinno);
	else if (arg0)
		outfmt(out2, "%s: ", arg0);
	outfmt(out2, "Syntax error: %s\n", msg);
	error((char *)NULL);
}