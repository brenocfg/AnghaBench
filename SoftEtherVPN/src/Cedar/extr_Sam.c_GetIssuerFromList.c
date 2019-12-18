#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  issuer_name; int /*<<< orphan*/  subject_name; } ;
typedef  TYPE_1__ X ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 scalar_t__ CheckSignature (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CheckXDateNow (TYPE_1__*) ; 
 scalar_t__ CompareName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CompareX (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetKFromX (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

X *GetIssuerFromList(LIST *cert_list, X *cert)
{
	UINT i;
	X *ret = NULL;
	// Validate arguments
	if (cert_list == NULL || cert == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(cert_list);i++)
	{
		X *x = LIST_DATA(cert_list, i);
		// Name comparison
		if (CheckXDateNow(x))
		{
			if (CompareName(x->subject_name, cert->issuer_name))
			{
				// Get the public key of the root certificate
				K *k = GetKFromX(x);

				if (k != NULL)
				{
					// Check the signature
					if (CheckSignature(cert, k))
					{
						ret = x;
					}
					FreeK(k);
				}
			}
		}
		if (CompareX(x, cert))
		{
			// Complete identical
			ret = x;
		}
	}

	return ret;
}