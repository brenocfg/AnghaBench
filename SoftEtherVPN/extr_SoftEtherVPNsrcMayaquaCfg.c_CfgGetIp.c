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
struct IP {int dummy; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int MAX_SIZE ; 
 int StrToIP (struct IP*,char*) ; 
 int /*<<< orphan*/  Zero (struct IP*,int) ; 

bool CfgGetIp(FOLDER *f, char *name, struct IP *ip)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (f == NULL || name == NULL || ip == NULL)
	{
		return false;
	}

	Zero(ip, sizeof(IP));

	if (CfgGetStr(f, name, tmp, sizeof(tmp)) == false)
	{
		return false;
	}

	if (StrToIP(ip, tmp) == false)
	{
		return false;
	}

	return true;
}