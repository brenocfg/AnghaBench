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
typedef  int /*<<< orphan*/  SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  GetCurrentGetIpThreadNum () ; 
 int /*<<< orphan*/  GetGetIpThreadMaxNum () ; 
 int /*<<< orphan*/  ToStr3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT SiDebugProcGetCurrentGetIPThreadCount(SERVER *s, char *in_str, char *ret_str, UINT ret_str_size)
{
	char tmp1[64], tmp2[64];
	// Validate arguments
	if (s == NULL || in_str == NULL || ret_str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	ToStr3(tmp1, 0, GetCurrentGetIpThreadNum());
	ToStr3(tmp2, 0, GetGetIpThreadMaxNum());

	Format(ret_str, 0, 
		"Current threads = %s\n"
		"Quota           = %s\n",
		tmp1, tmp2);

	return ERR_NO_ERROR;
}