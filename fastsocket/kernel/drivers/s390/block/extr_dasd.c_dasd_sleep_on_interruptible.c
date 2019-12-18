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
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int _dasd_sleep_on (struct dasd_ccw_req*,int) ; 

int dasd_sleep_on_interruptible(struct dasd_ccw_req *cqr)
{
	return _dasd_sleep_on(cqr, 1);
}