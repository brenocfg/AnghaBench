#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; } ;
struct TYPE_4__ {int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  FilePath; } ;
typedef  TYPE_1__ RPC_ENUM_LOG_FILE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumLogFile(PACK *p, RPC_ENUM_LOG_FILE *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);

	PackSetCurrentJsonGroupName(p, "LogFiles");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_LOG_FILE_ITEM *e = &t->Items[i];

		PackAddStrEx(p, "FilePath", e->FilePath, i, t->NumItem);
		PackAddStrEx(p, "ServerName", e->ServerName, i, t->NumItem);
		PackAddIntEx(p, "FileSize", e->FileSize, i, t->NumItem);
		PackAddTime64Ex(p, "UpdatedTime", e->UpdatedTime, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}