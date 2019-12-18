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
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ gdb_client ;

/* Variables and functions */
 int /*<<< orphan*/  SH2BreakNow (int /*<<< orphan*/ ) ; 

void gdb_client_break(gdb_client * client)
{
   SH2BreakNow(client->context);
}