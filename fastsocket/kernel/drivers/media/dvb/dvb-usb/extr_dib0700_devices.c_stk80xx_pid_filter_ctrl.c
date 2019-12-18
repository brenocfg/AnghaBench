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
struct dvb_usb_adapter {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int dib8000_pid_filter_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk80xx_pid_filter_ctrl(struct dvb_usb_adapter *adapter,
	int onoff)
{
    return dib8000_pid_filter_ctrl(adapter->fe, onoff);
}