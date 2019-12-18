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
struct brcms_c_info {int /*<<< orphan*/  bandlocked; TYPE_1__* pub; } ;
struct TYPE_2__ {int _nbands; } ;

/* Variables and functions */

__attribute__((used)) static bool brcms_is_mband_unlocked(struct brcms_c_info *wlc)
{
	return wlc->pub->_nbands > 1 && !wlc->bandlocked;
}