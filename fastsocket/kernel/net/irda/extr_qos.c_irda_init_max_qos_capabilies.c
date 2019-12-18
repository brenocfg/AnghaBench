#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int bits; } ;
struct TYPE_13__ {int bits; } ;
struct TYPE_12__ {int bits; } ;
struct TYPE_11__ {int bits; } ;
struct TYPE_10__ {int bits; } ;
struct TYPE_9__ {int bits; } ;
struct TYPE_8__ {int bits; } ;
struct qos_info {TYPE_7__ additional_bofs; TYPE_6__ link_disc_time; TYPE_5__ data_size; TYPE_4__ max_turn_time; TYPE_3__ min_turn_time; TYPE_2__ window_size; TYPE_1__ baud_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  baud_rates ; 
 int /*<<< orphan*/  index_value (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_disc_times ; 
 int /*<<< orphan*/  sysctl_max_baud_rate ; 
 int /*<<< orphan*/  sysctl_max_noreply_time ; 
 int value_lower_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

void irda_init_max_qos_capabilies(struct qos_info *qos)
{
	int i;
	/*
	 *  These are the maximum supported values as specified on pages
	 *  39-43 in IrLAP
	 */

	/* Use sysctl to set some configurable values... */
	/* Set configured max speed */
	i = value_lower_bits(sysctl_max_baud_rate, baud_rates, 10,
			     &qos->baud_rate.bits);
	sysctl_max_baud_rate = index_value(i, baud_rates);

	/* Set configured max disc time */
	i = value_lower_bits(sysctl_max_noreply_time, link_disc_times, 8,
			     &qos->link_disc_time.bits);
	sysctl_max_noreply_time = index_value(i, link_disc_times);

	/* LSB is first byte, MSB is second byte */
	qos->baud_rate.bits    &= 0x03ff;

	qos->window_size.bits     = 0x7f;
	qos->min_turn_time.bits   = 0xff;
	qos->max_turn_time.bits   = 0x0f;
	qos->data_size.bits       = 0x3f;
	qos->link_disc_time.bits &= 0xff;
	qos->additional_bofs.bits = 0xff;
}