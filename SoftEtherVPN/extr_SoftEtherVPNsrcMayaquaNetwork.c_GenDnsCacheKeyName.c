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
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 

void GenDnsCacheKeyName(char *dst, UINT size, char *src, bool ipv6)
{
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	if (ipv6 == false)
	{
		StrCpy(dst, size, src);
	}
	else
	{
		Format(dst, size, "%s@ipv6", src);
	}
}