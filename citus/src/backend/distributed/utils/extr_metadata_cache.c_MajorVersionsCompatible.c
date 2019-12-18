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
 char* strchr (char*,char const) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

bool
MajorVersionsCompatible(char *leftVersion, char *rightVersion)
{
	const char schemaVersionSeparator = '-';

	char *leftSeperatorPosition = strchr(leftVersion, schemaVersionSeparator);
	char *rightSeperatorPosition = strchr(rightVersion, schemaVersionSeparator);
	int leftComparisionLimit = 0;
	int rightComparisionLimit = 0;

	if (leftSeperatorPosition != NULL)
	{
		leftComparisionLimit = leftSeperatorPosition - leftVersion;
	}
	else
	{
		leftComparisionLimit = strlen(leftVersion);
	}

	if (rightSeperatorPosition != NULL)
	{
		rightComparisionLimit = rightSeperatorPosition - rightVersion;
	}
	else
	{
		rightComparisionLimit = strlen(leftVersion);
	}

	/* we can error out early if hypens are not in the same position */
	if (leftComparisionLimit != rightComparisionLimit)
	{
		return false;
	}

	return strncmp(leftVersion, rightVersion, leftComparisionLimit) == 0;
}