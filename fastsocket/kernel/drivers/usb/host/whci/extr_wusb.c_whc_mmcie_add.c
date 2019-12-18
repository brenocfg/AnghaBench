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
typedef  int u8 ;
typedef  int u32 ;
struct wusbhc {int dummy; } ;
struct wuie_hdr {int bLength; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WUSBGENCMDSTS_MMCIE_ADD ; 
 int whc_do_gencmd (struct whc*,int /*<<< orphan*/ ,int,struct wuie_hdr*,int) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

int whc_mmcie_add(struct wusbhc *wusbhc, u8 interval, u8 repeat_cnt,
		  u8 handle, struct wuie_hdr *wuie)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);
	u32 params;

	params = (interval << 24)
		| (repeat_cnt << 16)
		| (wuie->bLength << 8)
		| handle;

	return whc_do_gencmd(whc, WUSBGENCMDSTS_MMCIE_ADD, params, wuie, wuie->bLength);
}