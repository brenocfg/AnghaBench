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
typedef  size_t UINT ;
struct TYPE_3__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *ListToTokenList(LIST *o)
{
	UINT i;
	TOKEN_LIST *t;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	t = ZeroMalloc(sizeof(TOKEN_LIST));
	t->NumTokens = LIST_NUM(o);
	t->Token = ZeroMalloc(sizeof(char *) * t->NumTokens);
	for (i = 0;i < LIST_NUM(o);i++)
	{
		t->Token[i] = CopyStr(LIST_DATA(o, i));
	}

	return t;
}