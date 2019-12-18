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
typedef  int UINT ;
struct TYPE_4__ {void* String; } ;
typedef  TYPE_1__ RPC_STR ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcStr(RPC_STR *t, PACK *p)
{
	UINT size = 65536;
	char *tmp = Malloc(size);
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_STR));
	if (PackGetStr(p, "String", tmp, size) == false)
	{
		t->String = CopyStr("");
	}
	else
	{
		t->String = CopyStr(tmp);
	}
	Free(tmp);
}