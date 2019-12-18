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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct usb_line6_variax {TYPE_1__ activate_timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  variax_activate_timeout ; 

__attribute__((used)) static void variax_activate_delayed(struct usb_line6_variax *variax,
				    int seconds)
{
	variax->activate_timer.expires = jiffies + seconds * HZ;
	variax->activate_timer.function = variax_activate_timeout;
	variax->activate_timer.data = (unsigned long)variax;
	add_timer(&variax->activate_timer);
}