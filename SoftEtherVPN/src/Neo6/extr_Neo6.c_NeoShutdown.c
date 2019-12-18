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
struct TYPE_3__ {int /*<<< orphan*/  Status; } ;
typedef  int /*<<< orphan*/  NEO_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  NeoFreeStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoZero (TYPE_1__*,int) ; 
 TYPE_1__* ctx ; 

void NeoShutdown()
{
	if (ctx == NULL)
	{
		// Uninitialized
		return;
	}

	// Release the status information
	NeoFreeStatus(&ctx->Status);

	NeoZero(ctx, sizeof(NEO_CTX));
}