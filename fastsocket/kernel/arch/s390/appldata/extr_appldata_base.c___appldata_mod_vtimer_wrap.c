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
typedef  int /*<<< orphan*/  u64 ;
struct vtimer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_virt_timer_periodic (struct vtimer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __appldata_mod_vtimer_wrap(void *p) {
	struct {
		struct vtimer_list *timer;
		u64    expires;
	} *args = p;
	mod_virt_timer_periodic(args->timer, args->expires);
}