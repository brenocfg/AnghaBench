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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniCopyStr (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

UNI_TOKEN_LIST *UniListToTokenList(LIST *o)
{
	UINT i;
	UNI_TOKEN_LIST *t;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	t = ZeroMalloc(sizeof(UNI_TOKEN_LIST));
	t->NumTokens = LIST_NUM(o);
	t->Token = ZeroMalloc(sizeof(wchar_t *) * t->NumTokens);
	for (i = 0;i < LIST_NUM(o);i++)
	{
		t->Token[i] = UniCopyStr(LIST_DATA(o, i));
	}

	return t;
}