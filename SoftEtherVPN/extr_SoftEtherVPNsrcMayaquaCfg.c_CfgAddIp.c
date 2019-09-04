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
typedef  int /*<<< orphan*/  ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,struct IP*) ; 
 int MAX_SIZE ; 

ITEM *CfgAddIp(FOLDER *f, char *name, struct IP *ip)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (f == NULL || name == NULL || ip == NULL)
	{
		return NULL;
	}

	IPToStr(tmp, sizeof(tmp), ip);

	return CfgAddStr(f, name, tmp);
}