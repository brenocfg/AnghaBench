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
struct xt_tgdtor_param {struct xt_led_info* targinfo; } ;
struct xt_led_info_internal {int /*<<< orphan*/  netfilter_led_trigger; int /*<<< orphan*/  timer; } ;
struct xt_led_info {scalar_t__ delay; struct xt_led_info_internal* internal_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xt_led_info_internal*) ; 
 int /*<<< orphan*/  led_trigger_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_tg_destroy(const struct xt_tgdtor_param *par)
{
	const struct xt_led_info *ledinfo = par->targinfo;
	struct xt_led_info_internal *ledinternal = ledinfo->internal_data;

	if (ledinfo->delay > 0)
		del_timer_sync(&ledinternal->timer);

	led_trigger_unregister(&ledinternal->netfilter_led_trigger);
	kfree(ledinternal);
}