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
struct TYPE_4__ {int /*<<< orphan*/  p_param; int /*<<< orphan*/  (* p_exec_cback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ exec_cback; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void bta_dm_execute_callback(tBTA_DM_MSG *p_data)
{
    /* sanity check */
    if (p_data->exec_cback.p_exec_cback == NULL) {
        return;
    }

    p_data->exec_cback.p_exec_cback(p_data->exec_cback.p_param);
}