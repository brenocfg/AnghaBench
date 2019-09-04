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
struct TYPE_12__ {int /*<<< orphan*/  issuer_url; scalar_t__ root_cert; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CheckXEx (TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  CloneX (TYPE_1__*) ; 
 int CompareX (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* DownloadCert (int /*<<< orphan*/ ) ; 
 scalar_t__ FIND_CERT_CHAIN_MAX_DEPTH ; 
 TYPE_1__* FindCertIssuerFromCertList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (TYPE_1__*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

bool TryGetParentCertFromCertList(LIST *o, X *x, LIST *found_chain)
{
	bool ret = false;
	X *r;
	bool do_free = false;
	// Validate arguments
	if (o == NULL || x == NULL || found_chain == NULL)
	{
		return false;
	}

	if (LIST_NUM(found_chain) >= FIND_CERT_CHAIN_MAX_DEPTH)
	{
		return false;
	}

	Add(found_chain, CloneX(x));

	if (x->root_cert)
	{
		return true;
	}

	r = FindCertIssuerFromCertList(o, x);

	if (r == NULL)
	{
		if (IsEmptyStr(x->issuer_url) == false)
		{
			r = DownloadCert(x->issuer_url);

			if (CheckXEx(x, r, true, true) && CompareX(x, r) == false)
			{
				// found
				do_free = true;
			}
			else
			{
				// invalid
				FreeX(r);
				r = NULL;
			}
		}
	}

	if (r != NULL)
	{
		ret = TryGetParentCertFromCertList(o, r, found_chain);
	}

	if (do_free)
	{
		FreeX(r);
	}

	return ret;
}