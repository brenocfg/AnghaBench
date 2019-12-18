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
struct TYPE_2__ {int slot_mask; int /*<<< orphan*/ * CH; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_channels (int /*<<< orphan*/ *) ; 
 TYPE_1__ ym2612 ; 

void YM2612PicoStateLoad_(void)
{
	reset_channels( &ym2612.CH[0] );
	ym2612.slot_mask = 0xffffff;
}