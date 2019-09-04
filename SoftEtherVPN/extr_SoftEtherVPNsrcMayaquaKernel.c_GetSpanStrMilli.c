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
typedef  int /*<<< orphan*/  tmp ;
typedef  int UINT64 ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,...) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void GetSpanStrMilli(char *str, UINT size, UINT64 sec64)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	StrCpy(tmp, sizeof(tmp), "");
	if (sec64 >= (UINT64)(1000 * 3600 * 24))
	{
		Format(tmp, sizeof(tmp), "%u:", (UINT)(sec64 / (UINT64)(1000 * 3600 * 24)));
	}

	Format(tmp, sizeof(tmp), "%s%02u:%02u:%02u.%03u", tmp,
		(UINT)(sec64 % (UINT64)(1000 * 60 * 60 * 24)) / (1000 * 60 * 60),
		(UINT)(sec64 % (UINT64)(1000 * 60 * 60)) / (1000 * 60),
		(UINT)(sec64 % (UINT64)(1000 * 60)) / 1000,
		(UINT)(sec64 % (UINT64)(1000)));

	Trim(tmp);
	StrCpy(str, size, tmp);
}