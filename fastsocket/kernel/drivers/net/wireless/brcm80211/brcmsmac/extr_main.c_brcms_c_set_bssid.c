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
struct brcms_bss_cfg {int /*<<< orphan*/  BSSID; int /*<<< orphan*/  wlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCM_BSSID_OFFSET ; 
 int /*<<< orphan*/  brcms_c_set_addrmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_set_bssid(struct brcms_bss_cfg *bsscfg)
{
	/* we need to update BSSID in RXE match registers */
	brcms_c_set_addrmatch(bsscfg->wlc, RCM_BSSID_OFFSET, bsscfg->BSSID);
}