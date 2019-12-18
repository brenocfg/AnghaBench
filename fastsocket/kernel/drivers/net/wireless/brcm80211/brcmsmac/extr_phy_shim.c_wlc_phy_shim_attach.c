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
struct phy_shim_info {struct brcms_info* wl; struct brcms_c_info* wlc; struct brcms_hardware* wlc_hw; } ;
struct brcms_info {int dummy; } ;
struct brcms_hardware {int dummy; } ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct phy_shim_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct phy_shim_info *wlc_phy_shim_attach(struct brcms_hardware *wlc_hw,
					  struct brcms_info *wl,
					  struct brcms_c_info *wlc) {
	struct phy_shim_info *physhim = NULL;

	physhim = kzalloc(sizeof(struct phy_shim_info), GFP_ATOMIC);
	if (!physhim)
		return NULL;

	physhim->wlc_hw = wlc_hw;
	physhim->wlc = wlc;
	physhim->wl = wl;

	return physhim;
}