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
struct TYPE_3__ {int /*<<< orphan*/  mrso_name; } ;
typedef  TYPE_1__ mach_right_send_once_t ;

/* Variables and functions */
 int MACH_PORT_VALID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
mach_right_send_once_valid(mach_right_send_once_t mrso)
{
	return MACH_PORT_VALID(mrso.mrso_name);
}