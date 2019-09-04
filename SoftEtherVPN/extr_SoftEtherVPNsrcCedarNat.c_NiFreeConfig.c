#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  AdminK; int /*<<< orphan*/  AdminX; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/ * CfgRw; } ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeCfgRw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NiWriteConfig (TYPE_1__*) ; 

void NiFreeConfig(NAT *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	// Write the latest configuration
	NiWriteConfig(n);

	// Release the configuration R/W
	FreeCfgRw(n->CfgRw);
	n->CfgRw = NULL;

	Free(n->ClientOption);
	CiFreeClientAuth(n->ClientAuth);

	FreeX(n->AdminX);
	FreeK(n->AdminK);
}