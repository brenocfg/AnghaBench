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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  KEY_GC_REAP_KEYTYPE ; 
 TYPE_1__ current_kernel_time () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kdebug (char*) ; 
 int /*<<< orphan*/  kenter (char*,scalar_t__) ; 
 int /*<<< orphan*/  key_gc_flags ; 
 scalar_t__ key_gc_next_run ; 
 int /*<<< orphan*/  key_gc_timer ; 
 int /*<<< orphan*/  key_schedule_gc_work () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void key_schedule_gc(time_t gc_at)
{
	unsigned long expires;
	time_t now = current_kernel_time().tv_sec;

	kenter("%ld", gc_at - now);

	if (gc_at <= now || test_bit(KEY_GC_REAP_KEYTYPE, &key_gc_flags)) {
		kdebug("IMMEDIATE");
		key_schedule_gc_work();
	} else if (gc_at < key_gc_next_run) {
		kdebug("DEFERRED");
		key_gc_next_run = gc_at;
		expires = jiffies + (gc_at - now) * HZ;
		mod_timer(&key_gc_timer, expires);
	}
}