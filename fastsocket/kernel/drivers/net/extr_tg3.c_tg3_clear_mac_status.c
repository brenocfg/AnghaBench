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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_EVENT ; 
 int /*<<< orphan*/  MAC_STATUS ; 
 int MAC_STATUS_CFG_CHANGED ; 
 int MAC_STATUS_LNKSTATE_CHANGED ; 
 int MAC_STATUS_MI_COMPLETION ; 
 int MAC_STATUS_SYNC_CHANGED ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tg3_clear_mac_status(struct tg3 *tp)
{
	tw32(MAC_EVENT, 0);

	tw32_f(MAC_STATUS,
	       MAC_STATUS_SYNC_CHANGED |
	       MAC_STATUS_CFG_CHANGED |
	       MAC_STATUS_MI_COMPLETION |
	       MAC_STATUS_LNKSTATE_CHANGED);
	udelay(40);
}