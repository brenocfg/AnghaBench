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
struct TYPE_7__ {int /*<<< orphan*/  SrcAddress; int /*<<< orphan*/  SrcIP; } ;
struct TYPE_5__ {TYPE_3__* ARPv4Header; } ;
struct TYPE_6__ {TYPE_1__ L3; } ;
typedef  TYPE_2__ PKT ;
typedef  int /*<<< orphan*/  L3IF ;
typedef  TYPE_3__ ARPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  L3KnownArp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void L3RecvArpResponse(L3IF *f, PKT *p)
{
	ARPV4_HEADER *a;
	// Validate arguments
	if (f == NULL || p == NULL)
	{
		return;
	}

	a = p->L3.ARPv4Header;

	L3KnownArp(f, a->SrcIP, a->SrcAddress);
}