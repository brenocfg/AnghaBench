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
struct TYPE_4__ {int /*<<< orphan*/  AcList; void* CrlList; void* RootCertList; void* UserList; void* GroupList; } ;
typedef  TYPE_1__ HUBDB ;

/* Variables and functions */
 int /*<<< orphan*/ * CompareCert ; 
 int /*<<< orphan*/ * CompareGroupName ; 
 int /*<<< orphan*/ * CompareUserName ; 
 int /*<<< orphan*/  NewAcList () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

HUBDB *NewHubDb()
{
	HUBDB *d = ZeroMalloc(sizeof(HUBDB));

	d->GroupList = NewList(CompareGroupName);
	d->UserList = NewList(CompareUserName);
	d->RootCertList = NewList(CompareCert);
	d->CrlList = NewList(NULL);
	d->AcList = NewAcList();

	return d;
}