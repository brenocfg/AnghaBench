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
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ ToInt (int /*<<< orphan*/ ) ; 

UINT ViVersionStrToBuild(char *str)
{
	TOKEN_LIST *t;
	UINT ret;
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	t = ParseToken(str, ".");
	if (t == NULL)
	{
		return 0;
	}

	ret = 0;

	if (t->NumTokens == 3)
	{
		ret = ToInt(t->Token[2]);
	}

	FreeToken(t);

	return ret;
}