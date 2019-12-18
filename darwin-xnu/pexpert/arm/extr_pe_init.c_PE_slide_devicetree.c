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
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  deviceTreeHead; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTInit (int /*<<< orphan*/ ) ; 
 TYPE_1__ PE_state ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
PE_slide_devicetree(vm_offset_t slide)
{
	assert(PE_state.initialized);
	PE_state.deviceTreeHead += slide;
	DTInit(PE_state.deviceTreeHead);
}