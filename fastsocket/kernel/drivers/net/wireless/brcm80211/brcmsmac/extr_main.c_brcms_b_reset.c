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
struct brcms_hardware {int /*<<< orphan*/  wlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_USE_COREFLAGS ; 
 int /*<<< orphan*/  brcms_b_corereset (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_flushqueues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_deviceremoved (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_b_reset(struct brcms_hardware *wlc_hw)
{
	/* reset the core */
	if (!brcms_deviceremoved(wlc_hw->wlc))
		brcms_b_corereset(wlc_hw, BRCMS_USE_COREFLAGS);

	/* purge the dma rings */
	brcms_c_flushqueues(wlc_hw->wlc);
}