#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Expires; int /*<<< orphan*/  SystemId; int /*<<< orphan*/  Valid; } ;
struct TYPE_8__ {TYPE_6__* LicenseStatus; int /*<<< orphan*/ * LicenseSystem; } ;
struct TYPE_7__ {int /*<<< orphan*/  SystemExpires; int /*<<< orphan*/  SystemId; int /*<<< orphan*/  Valid; } ;
typedef  TYPE_1__ RPC_EL_LICENSE_STATUS ;
typedef  int /*<<< orphan*/  LICENSE_SYSTEM ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ElParseCurrentLicenseStatus (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT EtGetLicenseStatus(EL *e, RPC_EL_LICENSE_STATUS *t)
{
	UINT ret = ERR_NO_ERROR;
	LICENSE_SYSTEM *ls = e->LicenseSystem;

	if (ls == NULL)
	{
		return ERR_NOT_SUPPORTED;
	}

	Zero(t, sizeof(RPC_EL_LICENSE_STATUS));

	// Get the current license status
	ElParseCurrentLicenseStatus(ls, e->LicenseStatus);

	t->Valid = e->LicenseStatus->Valid;
	t->SystemId = e->LicenseStatus->SystemId;
	t->SystemExpires = e->LicenseStatus->Expires;

	return ret;
}