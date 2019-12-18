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
struct TYPE_2__ {int MAS0; int /*<<< orphan*/  MAS1; } ;

/* Variables and functions */
 int MAS0_ESEL (int) ; 
 int MAS0_TLBSEL (int) ; 
 int /*<<< orphan*/  MAS1_VALID ; 
 TYPE_1__* TLBCAM ; 
 int /*<<< orphan*/  loadcam_entry (int) ; 

void invalidate_tlbcam_entry(int index)
{
	TLBCAM[index].MAS0 = MAS0_TLBSEL(1) | MAS0_ESEL(index);
	TLBCAM[index].MAS1 = ~MAS1_VALID;

	loadcam_entry(index);
}