#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sysfd; TYPE_1__* current_func_ver; } ;
struct TYPE_7__ {int /*<<< orphan*/  sysfd; } ;
struct TYPE_6__ {TYPE_2__ perf; } ;
typedef  TYPE_2__ CheckasmPerf ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ state ; 

CheckasmPerf *checkasm_get_perf_context(void)
{
    CheckasmPerf *perf = &state.current_func_ver->perf;
    memset(perf, 0, sizeof(*perf));
    perf->sysfd = state.sysfd;
    return perf;
}