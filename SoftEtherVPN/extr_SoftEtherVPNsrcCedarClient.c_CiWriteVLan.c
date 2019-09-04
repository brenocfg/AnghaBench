#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/  Enabled; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ UNIX_VLAN ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 

void CiWriteVLan(CLIENT *c, FOLDER *f, UNIX_VLAN *v)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (c == NULL || f == NULL || v == NULL)
	{
		return;
	}

	MacToStr(tmp, sizeof(tmp), v->MacAddress);
	CfgAddStr(f, "MacAddress", tmp);
	CfgAddBool(f, "Enabled", v->Enabled);
}