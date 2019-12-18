#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ TypeL4; scalar_t__ PayloadSize; int /*<<< orphan*/ * Payload; } ;
typedef  TYPE_1__ PKT ;

/* Variables and functions */
 scalar_t__ INFINITE ; 
 scalar_t__ L4_TCP ; 
 scalar_t__ SearchBin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

bool IsTcpPacketNcsiHttpAccess(PKT *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return false;
	}

	if (p->TypeL4 != L4_TCP)
	{
		return false;
	}

	if (p->Payload == NULL || p->PayloadSize == 0)
	{
		return false;
	}

	if (SearchBin(p->Payload, 0, p->PayloadSize, "NCSI", 4) != INFINITE)
	{
		return true;
	}

	if (SearchBin(p->Payload, 0, p->PayloadSize, ".jpeg", 5) != INFINITE)
	{
		return true;
	}

	if (SearchBin(p->Payload, 0, p->PayloadSize, ".jpg", 4) != INFINITE)
	{
		return true;
	}

	if (SearchBin(p->Payload, 0, p->PayloadSize, ".gif", 4) != INFINITE)
	{
		return true;
	}

	if (SearchBin(p->Payload, 0, p->PayloadSize, ".css", 4) != INFINITE)
	{
		return true;
	}

	return false;
}