#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  AutoDeleteCheckDiskFreeSpaceMin; int /*<<< orphan*/  Eraser; int /*<<< orphan*/  LicenseStatus; int /*<<< orphan*/  LicenseSystem; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  ElInitConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  ElParseCurrentLicenseStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ElStartListener (TYPE_1__*) ; 
 int /*<<< orphan*/  InitEth () ; 
 int /*<<< orphan*/  NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewEraser (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  RegistWindowsFirewallAll () ; 
 TYPE_1__* ZeroMalloc (int) ; 

EL *NewEl()
{
	EL *e;

#ifdef OS_WIN32
	RegistWindowsFirewallAll();
#endif

	e = ZeroMalloc(sizeof(EL));
	e->lock = NewLock();
	e->ref = NewRef();

	e->Cedar = NewCedar(NULL, NULL);


	// Ethernet initialization
	InitEth();

	// Setting initialization
	ElInitConfig(e);

	// Listener start
	ElStartListener(e);

	// Initialize the license status
	ElParseCurrentLicenseStatus(e->LicenseSystem, e->LicenseStatus);

	// Eraser start
	e->Eraser = NewEraser(NULL, e->AutoDeleteCheckDiskFreeSpaceMin);

	return e;
}