#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mach_right_send_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;

/* Variables and functions */

__attribute__((used)) static inline mach_right_send_t
mach_right_send(mach_port_name_t pn)
{
	mach_right_send_t mrs = {pn};
	return mrs;
}