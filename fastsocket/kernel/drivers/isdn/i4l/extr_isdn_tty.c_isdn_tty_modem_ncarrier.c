#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {TYPE_3__ nc_timer; scalar_t__ ncarrier; } ;
typedef  TYPE_1__ modem_info ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
isdn_tty_modem_ncarrier(modem_info * info)
{
	if (info->ncarrier) {
		info->nc_timer.expires = jiffies + HZ;
		add_timer(&info->nc_timer);
	}
}