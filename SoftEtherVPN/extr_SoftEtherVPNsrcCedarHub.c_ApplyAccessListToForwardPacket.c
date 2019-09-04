#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_21__ {scalar_t__ DestUsernameHash; scalar_t__ Discard; } ;
struct TYPE_20__ {int /*<<< orphan*/  AccessList; } ;
struct TYPE_19__ {int /*<<< orphan*/  GroupnameHash; int /*<<< orphan*/  UsernameHash; } ;
struct TYPE_18__ {scalar_t__ AccessChecked; } ;
struct TYPE_17__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_16__ {scalar_t__ Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ PKT ;
typedef  TYPE_4__ HUB_PA ;
typedef  TYPE_5__ HUB ;
typedef  TYPE_6__ ACCESS ;

/* Variables and functions */
 scalar_t__ IsPacketMaskedByAccessList (TYPE_2__*,TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_6__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool ApplyAccessListToForwardPacket(HUB *hub, SESSION *src_session, SESSION *dest_session, PKT *p)
{
	UINT i;
	bool pass = true;	// Pass by default
	bool skip = true;
	// Validate arguments
	if (hub == NULL || src_session == NULL || p == NULL || dest_session == NULL)
	{
		return false;
	}

	// The access list is not re-applied for packets that have been already checked
	if (p->AccessChecked)
	{
		return true;
	}

	LockList(hub->AccessList);
	{
		for (i = 0;i < LIST_NUM(hub->AccessList);i++)
		{
			ACCESS *a = LIST_DATA(hub->AccessList, i);

			// Scan the entry only after the destination user name is specified.
			if (a->DestUsernameHash != 0)
			{
				skip = false;
			}

			if (skip == false)
			{
				if (IsPacketMaskedByAccessList(src_session, p, a,
					((HUB_PA *)dest_session->PacketAdapter->Param)->UsernameHash,
					((HUB_PA *)dest_session->PacketAdapter->Param)->GroupnameHash,
					dest_session))
				{
					// Determine the pass or discard the packet
					pass = a->Discard ? false : true;

					// Complete the scanning of the list here
					break;
				}
			}
		}
	}
	UnlockList(hub->AccessList);

	return pass;
}