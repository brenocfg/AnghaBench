#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int Deleting; int /*<<< orphan*/  ResponderCookie; int /*<<< orphan*/  InitiatorCookie; int /*<<< orphan*/  IkeClient; } ;
struct TYPE_8__ {int StateHasChanged; } ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ IKE_SA ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPsecLog (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SendDeleteIkeSaPacket (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void MarkIkeSaAsDeleted(IKE_SERVER *ike, IKE_SA *sa)
{
	// Validate arguments
	if (ike == NULL || sa == NULL)
	{
		return;
	}

	if (sa->Deleting)
	{
		return;
	}

	ike->StateHasChanged = true;

	sa->Deleting = true;

	Debug("IKE SA %I64u - %I64u has been marked as being deleted.\n", sa->InitiatorCookie, sa->ResponderCookie);

	SendDeleteIkeSaPacket(ike, sa->IkeClient, sa->InitiatorCookie, sa->ResponderCookie);

	IPsecLog(ike, NULL, sa, NULL, "LI_DELETE_IKE_SA");
}