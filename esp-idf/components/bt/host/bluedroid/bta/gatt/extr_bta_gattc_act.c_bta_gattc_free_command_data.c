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
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
struct TYPE_3__ {int /*<<< orphan*/ * p_q_cmd; int /*<<< orphan*/  p_cmd_list; } ;
typedef  TYPE_1__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/ *) ; 
 scalar_t__ list_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void bta_gattc_free_command_data(tBTA_GATTC_CLCB *p_clcb)
{
    assert(p_clcb->p_cmd_list);
    //Check the list is empty or not.
    if (!list_is_empty(p_clcb->p_cmd_list)) {
        /* Traversal the command queue, check the p_q_cmd is point to the queue data or not, if the p_q_cmd point to the
           command queue,should remove it from the list */
        for (list_node_t *node = list_begin(p_clcb->p_cmd_list); node != list_end(p_clcb->p_cmd_list);
             node = list_next(node)) {
            tBTA_GATTC_DATA *p_data = (tBTA_GATTC_DATA *)list_node(node);
            if (p_data == p_clcb->p_q_cmd) {
                list_remove(p_clcb->p_cmd_list, (void *)p_data);
                p_clcb->p_q_cmd = NULL;
                return;
            }
        }

        osi_free(p_clcb->p_q_cmd);
        p_clcb->p_q_cmd = NULL;
    } else {
        osi_free(p_clcb->p_q_cmd);
        p_clcb->p_q_cmd = NULL;
    }
}