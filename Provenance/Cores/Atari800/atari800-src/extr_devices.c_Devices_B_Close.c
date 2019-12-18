#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pos; int /*<<< orphan*/  ready; int /*<<< orphan*/  url; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Log_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ dev_b_status ; 
 scalar_t__ devbug ; 

__attribute__((used)) static void Devices_B_Close(void)
{
	if (devbug)
		Log_print("B: CLOSE (%s)", dev_b_status.url);

	if (dev_b_status.pos > 0)
		dev_b_status.ready = TRUE;

	CPU_regY = 1;
	CPU_ClrN;
}