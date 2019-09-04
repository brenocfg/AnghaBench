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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 

bool GetEnv(char *name, char *data, UINT size)
{
	char *ret;
	// Validate arguments
	if (name == NULL || data == NULL)
	{
		return false;
	}

	StrCpy(data, size, "");

	ret = getenv(name);
	if (ret == NULL)
	{
		return false;
	}

	StrCpy(data, size, ret);

	return true;
}