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
struct brcms_cm_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct brcms_cm_info*) ; 

void brcms_c_channel_mgr_detach(struct brcms_cm_info *wlc_cm)
{
	kfree(wlc_cm);
}