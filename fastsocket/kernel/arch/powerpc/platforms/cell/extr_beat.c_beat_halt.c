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
 int /*<<< orphan*/  beat_halt_code ; 
 int /*<<< orphan*/  beat_shutdown_logical_partition (int /*<<< orphan*/ ) ; 

void beat_halt(void)
{
	beat_shutdown_logical_partition(beat_halt_code);
}