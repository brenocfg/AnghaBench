#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {TYPE_2__* TagVlanHeader; } ;
struct TYPE_7__ {int VlanId; TYPE_1__ L3; int /*<<< orphan*/  TypeL3; } ;
struct TYPE_6__ {int /*<<< orphan*/  Data; } ;
typedef  TYPE_2__ TAGVLAN_HEADER ;
typedef  TYPE_3__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  L3_TAGVLAN ; 
 int READ_USHORT (int /*<<< orphan*/ ) ; 

bool ParsePacketTAGVLAN(PKT *p, UCHAR *buf, UINT size)
{
	USHORT vlan_ushort;
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(TAGVLAN_HEADER))
	{
		return false;
	}

	// TAG VLAN header
	p->L3.TagVlanHeader = (TAGVLAN_HEADER *)buf;
	p->TypeL3 = L3_TAGVLAN;

	buf += sizeof(TAGVLAN_HEADER);
	size -= sizeof(TAGVLAN_HEADER);

	vlan_ushort = READ_USHORT(p->L3.TagVlanHeader->Data);
	vlan_ushort = vlan_ushort & 0xFFF;

	p->VlanId = vlan_ushort;

	return true;
}