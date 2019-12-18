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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dell_rfkill_work ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool dell_laptop_i8042_filter(unsigned char data, unsigned char str,
			      struct serio *port)
{
	static bool extended;

	if (str & 0x20)
		return false;

	if (unlikely(data == 0xe0)) {
		extended = true;
		return false;
	} else if (unlikely(extended)) {
		switch (data) {
		case 0x8:
			schedule_delayed_work(&dell_rfkill_work,
					      round_jiffies_relative(HZ));
			break;
		}
		extended = false;
	}

	return false;
}