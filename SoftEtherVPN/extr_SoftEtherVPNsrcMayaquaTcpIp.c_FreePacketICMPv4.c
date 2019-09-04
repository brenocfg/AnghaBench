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
struct TYPE_4__ {int /*<<< orphan*/ * ICMPHeader; } ;
struct TYPE_5__ {int /*<<< orphan*/  TypeL4; TYPE_1__ L4; } ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  L4_UNKNOWN ; 

void FreePacketICMPv4(PKT *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	p->L4.ICMPHeader = NULL;
	p->TypeL4 = L4_UNKNOWN;
}