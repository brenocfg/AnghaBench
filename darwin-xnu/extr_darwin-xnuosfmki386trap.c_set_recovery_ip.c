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
struct TYPE_4__ {int /*<<< orphan*/  rip; } ;
struct TYPE_5__ {TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */

__attribute__((used)) static void
set_recovery_ip(x86_saved_state64_t  *saved_state, vm_offset_t ip)
{
        saved_state->isf.rip = ip;
}