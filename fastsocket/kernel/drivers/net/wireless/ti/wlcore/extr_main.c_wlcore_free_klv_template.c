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
typedef  scalar_t__ u8 ;
struct wl1271 {int /*<<< orphan*/  klv_templates_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WLCORE_MAX_KLV_TEMPLATES ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlcore_free_klv_template(struct wl1271 *wl, u8 *idx)
{
	if (WARN_ON(*idx >= WLCORE_MAX_KLV_TEMPLATES))
		return;

	__clear_bit(*idx, wl->klv_templates_map);
	*idx = WLCORE_MAX_KLV_TEMPLATES;
}