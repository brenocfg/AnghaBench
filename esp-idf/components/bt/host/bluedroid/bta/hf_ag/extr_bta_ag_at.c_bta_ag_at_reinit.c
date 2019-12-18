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
struct TYPE_3__ {scalar_t__ cmd_pos; int /*<<< orphan*/ * p_cmd_buf; } ;
typedef  TYPE_1__ tBTA_AG_AT_CB ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void bta_ag_at_reinit(tBTA_AG_AT_CB *p_cb)
{
    if (p_cb->p_cmd_buf != NULL) {
        osi_free(p_cb->p_cmd_buf);
        p_cb->p_cmd_buf = NULL;
    }
    p_cb->cmd_pos = 0;
}