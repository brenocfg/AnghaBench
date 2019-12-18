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
struct brcms_hardware {int /*<<< orphan*/  d11core; } ;
struct brcms_c_info {int /*<<< orphan*/  macintmask; int /*<<< orphan*/  defmacintmask; struct brcms_hardware* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macintmask ; 

void brcms_c_intrson(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	wlc->macintmask = wlc->defmacintmask;
	bcma_write32(wlc_hw->d11core, D11REGOFFS(macintmask), wlc->macintmask);
}