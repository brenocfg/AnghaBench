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
struct TYPE_3__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  UserName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Id; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ETHERIP_ID ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutEtherIpId(PACK *p, ETHERIP_ID *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "Id", t->Id);
	PackAddStr(p, "HubName", t->HubName);
	PackAddStr(p, "UserName", t->UserName);
	PackAddStr(p, "Password", t->Password);
}