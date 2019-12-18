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
struct m920x_state {int* filtering_enabled; } ;
struct dvb_usb_adapter {size_t id; TYPE_1__* dev; } ;
struct TYPE_2__ {struct m920x_state* priv; } ;

/* Variables and functions */
 int m920x_update_filters (struct dvb_usb_adapter*) ; 

__attribute__((used)) static int m920x_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct m920x_state *m = adap->dev->priv;

	m->filtering_enabled[adap->id] = onoff ? 1 : 0;

	return m920x_update_filters(adap);
}