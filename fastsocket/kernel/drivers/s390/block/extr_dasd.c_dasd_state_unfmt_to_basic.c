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
struct dasd_device {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STATE_BASIC ; 

__attribute__((used)) static int dasd_state_unfmt_to_basic(struct dasd_device *device)
{
	device->state = DASD_STATE_BASIC;
	return 0;
}