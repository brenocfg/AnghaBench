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
struct TYPE_4__ {scalar_t__ root_cert; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  FreeCertList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewCertList (int) ; 
 int TryGetRootCertChain (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

bool DownloadAndSaveIntermediateCertificatesIfNecessary(X *x)
{
	LIST *o;
	bool ret = false;
	// Validate arguments
	if (x == NULL)
	{
		return false;
	}

	if (x->root_cert)
	{
		return true;
	}

	o = NewCertList(true);

	ret = TryGetRootCertChain(o, x, true, NULL);

	FreeCertList(o);

	return ret;
}