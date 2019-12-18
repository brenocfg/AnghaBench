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
struct TYPE_4__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_5__ {TYPE_1__ child_process; } ;
typedef  TYPE_2__ proc_instance_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ STILL_ACTIVE ; 

int proc_get_exit_code(proc_instance_t *inst)
{
    DWORD result;
    if (!GetExitCodeProcess(inst->child_process.hProcess, &result)) {
        return -2;
    }
    if (result == STILL_ACTIVE) {
        return -1;
    }
    return (int) result;
}