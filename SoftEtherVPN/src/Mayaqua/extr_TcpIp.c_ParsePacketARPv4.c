#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * ARPv4Header; } ;
struct TYPE_5__ {int /*<<< orphan*/  TypeL3; TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  int /*<<< orphan*/  ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  L3_ARPV4 ; 

bool ParsePacketARPv4(PKT *p, UCHAR *buf, UINT size)
{
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(ARPV4_HEADER))
	{
		return false;
	}

	// ARPv4 header
	p->L3.ARPv4Header = (ARPV4_HEADER *)buf;
	p->TypeL3 = L3_ARPV4;

	buf += sizeof(ARPV4_HEADER);
	size -= sizeof(ARPV4_HEADER);

	return true;
}