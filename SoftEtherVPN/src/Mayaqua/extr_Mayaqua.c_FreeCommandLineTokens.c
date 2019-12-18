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
 int /*<<< orphan*/  FreeToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFreeToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmdline_token ; 
 int /*<<< orphan*/ * cmdline_uni_token ; 

void FreeCommandLineTokens()
{
	if (cmdline_token != NULL)
	{
		FreeToken(cmdline_token);
	}
	cmdline_token = NULL;

	if (cmdline_uni_token != NULL)
	{
		UniFreeToken(cmdline_uni_token);
	}
	cmdline_uni_token = NULL;
}