#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_7__ {int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_CLIENT_DELETE_CA ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSetError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int DeleteCa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 

bool CtDeleteCa(CLIENT *c, RPC_CLIENT_DELETE_CA *p)
{
	bool ret;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return false;
	}

	ret = DeleteCa(c->Cedar, p->Key);

	if (ret == false)
	{
		CiSetError(c, ERR_OBJECT_NOT_FOUND);
	}

	CiSaveConfigurationFile(c);

	return ret;
}