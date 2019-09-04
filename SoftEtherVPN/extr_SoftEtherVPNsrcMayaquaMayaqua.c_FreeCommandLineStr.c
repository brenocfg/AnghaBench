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
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCommandLineStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * exename ; 
 int /*<<< orphan*/ * exename_w ; 

void FreeCommandLineStr()
{
	SetCommandLineStr(NULL);

	if (exename != NULL)
	{
		Free(exename);
		exename = NULL;
	}

	if (exename_w != NULL)
	{
		Free(exename_w);
		exename_w = NULL;
	}
}