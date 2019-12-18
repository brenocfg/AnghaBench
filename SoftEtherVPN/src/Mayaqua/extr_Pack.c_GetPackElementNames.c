#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  elements; } ;
struct TYPE_7__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ PACK ;
typedef  TYPE_3__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *GetPackElementNames(PACK *p)
{
	TOKEN_LIST *ret;
	UINT i;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(TOKEN_LIST));

	ret->NumTokens = LIST_NUM(p->elements);
	ret->Token = ZeroMalloc(sizeof(char *) * ret->NumTokens);

	for (i = 0;i < ret->NumTokens;i++)
	{
		ELEMENT *e = LIST_DATA(p->elements, i);

		ret->Token[i] = CopyStr(e->name);
	}

	return ret;
}