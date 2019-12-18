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
typedef  int u32 ;
struct de_private {int /*<<< orphan*/  media_timer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DE_TIMER_LINK ; 
 scalar_t__ DE_TIMER_NO_LINK ; 
 int LinkFail ; 
 int LinkPass ; 
 int /*<<< orphan*/  de_link_down (struct de_private*) ; 
 int /*<<< orphan*/  de_link_up (struct de_private*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void de_media_interrupt (struct de_private *de, u32 status)
{
	if (status & LinkPass) {
		de_link_up(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_LINK);
		return;
	}

	BUG_ON(!(status & LinkFail));

	if (netif_carrier_ok(de->dev)) {
		de_link_down(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_NO_LINK);
	}
}