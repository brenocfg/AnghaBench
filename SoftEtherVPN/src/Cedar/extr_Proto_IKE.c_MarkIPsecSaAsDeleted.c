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
struct TYPE_9__ {int StateHasChanged; } ;
struct TYPE_8__ {int Deleting; int /*<<< orphan*/  Spi; int /*<<< orphan*/  IkeClient; } ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPsecLog (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SendDeleteIPsecSaPacket (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void MarkIPsecSaAsDeleted(IKE_SERVER *ike, IPSECSA *sa)
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

	Debug("IPsec SA 0x%X has been marked as being deleted.\n", sa->Spi);

	SendDeleteIPsecSaPacket(ike, sa->IkeClient, sa->Spi);

	IPsecLog(ike, NULL, NULL, sa, "LI_DELETE_IPSEC_SA");
}