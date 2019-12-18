#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int slave_timeout; int /*<<< orphan*/  slave_timer; } ;
struct TYPE_5__ {TYPE_1__ dama; int /*<<< orphan*/ * values; } ;
typedef  TYPE_2__ ax25_dev ;

/* Variables and functions */
 size_t AX25_VALUES_DS_TIMEOUT ; 
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void ax25_ds_set_timer(ax25_dev *ax25_dev)
{
	if (ax25_dev == NULL)		/* paranoia */
		return;

	ax25_dev->dama.slave_timeout =
		msecs_to_jiffies(ax25_dev->values[AX25_VALUES_DS_TIMEOUT]) / 10;
	mod_timer(&ax25_dev->dama.slave_timer, jiffies + HZ);
}