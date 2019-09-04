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
struct TYPE_3__ {int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_1__ RPC_READ_LOG_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 

void FreeRpcReadLogFile(RPC_READ_LOG_FILE *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (t->Buffer != NULL)
	{
		FreeBuf(t->Buffer);
	}
}