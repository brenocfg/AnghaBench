#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  subject_name; int /*<<< orphan*/  issuer_name; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 int CheckSignature (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int CheckXDateNow (TYPE_1__*) ; 
 int CompareName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetKFromX (TYPE_1__*) ; 

bool CheckXEx(X *x, X *x_issuer, bool check_name, bool check_date)
{
	K *k;
	bool ret;
	// Validate arguments
	if (x == NULL || x_issuer == NULL)
	{
		return false;
	}

	k = GetKFromX(x_issuer);
	if (k == NULL)
	{
		return false;
	}

	ret = CheckSignature(x, k);

	if (ret)
	{
		if (check_name)
		{
			if (CompareName(x->issuer_name, x_issuer->subject_name) == false)
			{
				ret = false;
			}
		}

		if (check_date)
		{
			if (CheckXDateNow(x_issuer) == false)
			{
				ret = false;
			}
		}
	}

	FreeK(k);

	return ret;
}