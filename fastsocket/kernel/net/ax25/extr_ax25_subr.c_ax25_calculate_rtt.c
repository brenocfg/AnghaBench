#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ backoff; scalar_t__ n2count; int rtt; int t1; int /*<<< orphan*/  t1timer; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int AX25_T1CLAMPHI ; 
 int AX25_T1CLAMPLO ; 
 int ax25_display_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ ax25_t1timer_running (TYPE_1__*) ; 

void ax25_calculate_rtt(ax25_cb *ax25)
{
	if (ax25->backoff == 0)
		return;

	if (ax25_t1timer_running(ax25) && ax25->n2count == 0)
		ax25->rtt = (9 * ax25->rtt + ax25->t1 - ax25_display_timer(&ax25->t1timer)) / 10;

	if (ax25->rtt < AX25_T1CLAMPLO)
		ax25->rtt = AX25_T1CLAMPLO;

	if (ax25->rtt > AX25_T1CLAMPHI)
		ax25->rtt = AX25_T1CLAMPHI;
}