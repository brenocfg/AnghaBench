#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  issuer_name; int /*<<< orphan*/  subject_name; } ;
typedef  TYPE_1__ X ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 scalar_t__ CheckSignature (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CheckXDateNow (TYPE_1__*) ; 
 TYPE_1__* CloneX (TYPE_1__*) ; 
 scalar_t__ CompareName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CompareX (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetKFromX (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

X *FindCaSignedX(LIST *o, X *x)
{
	X *ret;
	// Validate arguments
	if (o == NULL || x == NULL)
	{
		return NULL;
	}

	ret = NULL;

	LockList(o);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(o);i++)
		{
			X *ca = LIST_DATA(o, i);
			if (CheckXDateNow(ca))
			{
				if (CompareName(ca->subject_name, x->issuer_name))
				{
					K *k = GetKFromX(ca);
					if (k != NULL)
					{
						if (CheckSignature(x, k))
						{
							ret = CloneX(ca);
						}
						FreeK(k);
					}
				}
				else if (CompareX(ca, x))
				{
					ret = CloneX(ca);
				}
			}

			if (ret != NULL)
			{
				break;
			}
		}
	}
	UnlockList(o);

	return ret;
}