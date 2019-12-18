#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;
struct TYPE_6__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_2__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyUniToStr (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *UniTokenListToTokenList(UNI_TOKEN_LIST *src)
{
	TOKEN_LIST *ret;
	UINT i;
	// Validate arguments
	if (src == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(TOKEN_LIST));
	ret->NumTokens = src->NumTokens;
	ret->Token = ZeroMalloc(sizeof(char *) * ret->NumTokens);

	for (i = 0;i < ret->NumTokens;i++)
	{
		ret->Token[i] = CopyUniToStr(src->Token[i]);
	}

	return ret;
}