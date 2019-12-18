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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_adapter {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int dib7000p_pid_filter (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk70x0p_pid_filter(struct dvb_usb_adapter *adapter, int index, u16 pid, int onoff)
{
    return dib7000p_pid_filter(adapter->fe, index, pid, onoff);
}