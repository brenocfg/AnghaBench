#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  FileData; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__ RPC_CONFIG ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ZeroMalloc (scalar_t__) ; 

void InRpcConfig(RPC_CONFIG *t, PACK *p)
{
	UINT size;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_CONFIG));
	PackGetStr(p, "FileName", t->FileName, sizeof(t->FileName));
	size = PackGetDataSize(p, "FileData");
	t->FileData = ZeroMalloc(size + 1);
	PackGetData(p, "FileData", t->FileData);
}