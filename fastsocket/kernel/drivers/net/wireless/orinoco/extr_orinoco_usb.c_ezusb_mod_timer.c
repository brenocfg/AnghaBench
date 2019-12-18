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
struct timer_list {int dummy; } ;
struct ezusb_priv {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (struct timer_list*,unsigned long) ; 

__attribute__((used)) static inline void ezusb_mod_timer(struct ezusb_priv *upriv,
				   struct timer_list *timer,
				   unsigned long expire)
{
	if (!upriv->udev)
		return;
	mod_timer(timer, expire);
}