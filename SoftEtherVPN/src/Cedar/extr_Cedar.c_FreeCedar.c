#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  FreeProtocol () ; 
 int /*<<< orphan*/  ProtoFree () ; 
 scalar_t__ init_cedar_counter ; 

void FreeCedar()
{
	if ((--init_cedar_counter) > 0)
	{
		return;
	}

	// Free third-party protocol interface
	ProtoFree();

	// Free protocol module
	FreeProtocol();
}