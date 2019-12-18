#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int UseNat; TYPE_4__* NatTable; TYPE_3__* NativeNat; } ;
typedef  TYPE_5__ VH ;
struct TYPE_11__ {scalar_t__ num_item; } ;
struct TYPE_10__ {TYPE_2__* NatTableForRecv; } ;
struct TYPE_9__ {TYPE_1__* AllList; } ;
struct TYPE_8__ {scalar_t__ num_item; } ;

/* Variables and functions */
 scalar_t__ NAT_MAX_SESSIONS ; 
 scalar_t__ NAT_MAX_SESSIONS_KERNEL ; 
 scalar_t__ NnIsActive (TYPE_5__*) ; 

bool CanCreateNewNatEntry(VH *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return false;
	}

	if (v->UseNat == false)
	{
		// NAT stopped
		return false;
	}

	if (NnIsActive(v) && v->NativeNat != NULL && v->NativeNat->NatTableForRecv != NULL)
	{
		if (v->NativeNat->NatTableForRecv->AllList->num_item > NAT_MAX_SESSIONS_KERNEL)
		{
			// Number of sessions exceeded (kernel mode)
			return false;
		}
	}
	else
	{
		if (v->NatTable->num_item > NAT_MAX_SESSIONS)
		{
			// Number of sessions exceeded (user mode)
			return false;
		}
	}

	return true;
}