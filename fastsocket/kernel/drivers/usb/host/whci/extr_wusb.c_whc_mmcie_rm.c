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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wusbhc {int dummy; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WUSBGENCMDSTS_MMCIE_RM ; 
 int whc_do_gencmd (struct whc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

int whc_mmcie_rm(struct wusbhc *wusbhc, u8 handle)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);
	u32 params;

	params = handle;

	return whc_do_gencmd(whc, WUSBGENCMDSTS_MMCIE_RM, params, NULL, 0);
}