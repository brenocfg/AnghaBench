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
 int /*<<< orphan*/  ApplyLogRedaction (char const*) ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ LogLocalCommands ; 
 scalar_t__ LogRemoteCommands ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LogLocalCommand(const char *command)
{
	if (!(LogRemoteCommands || LogLocalCommands))
	{
		return;
	}

	ereport(LOG, (errmsg("executing the command locally: %s",
						 ApplyLogRedaction(command))));
}