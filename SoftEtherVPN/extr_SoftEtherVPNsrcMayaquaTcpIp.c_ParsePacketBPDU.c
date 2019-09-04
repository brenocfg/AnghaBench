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
struct TYPE_4__ {int /*<<< orphan*/ * BpduHeader; } ;
struct TYPE_5__ {int /*<<< orphan*/  TypeL3; TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  int /*<<< orphan*/  BPDU_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  L3_BPDU ; 

bool ParsePacketBPDU(PKT *p, UCHAR *buf, UINT size)
{
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(BPDU_HEADER))
	{
		return true;
	}

	// BPDU header
	p->L3.BpduHeader = (BPDU_HEADER *)buf;
	p->TypeL3 = L3_BPDU;

	buf += sizeof(BPDU_HEADER);
	size -= sizeof(BPDU_HEADER);

	return true;
}