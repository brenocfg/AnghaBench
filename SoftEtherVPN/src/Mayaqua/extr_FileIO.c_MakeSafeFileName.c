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
typedef  int UINT ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  ReplaceStrEx (char*,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 

void MakeSafeFileName(char *dst, UINT size, char *src)
{
	char tmp[MAX_PATH];
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	StrCpy(tmp, sizeof(tmp), src);
	ReplaceStrEx(tmp, sizeof(tmp), tmp, "..", "__", false);
	ReplaceStrEx(tmp, sizeof(tmp), tmp, "/", "_", false);
	ReplaceStrEx(tmp, sizeof(tmp), tmp, "\\", "_", false);
	ReplaceStrEx(tmp, sizeof(tmp), tmp, "@", "_", false);
	ReplaceStrEx(tmp, sizeof(tmp), tmp, "|", "_", false);

	StrCpy(dst, size, tmp);
}