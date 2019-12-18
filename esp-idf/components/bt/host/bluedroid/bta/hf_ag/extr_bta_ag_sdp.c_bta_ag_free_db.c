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
struct TYPE_3__ {int /*<<< orphan*/ * p_disc_db; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void bta_ag_free_db(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_data);
    if (p_scb->p_disc_db != NULL) {
        osi_free(p_scb->p_disc_db);
        p_scb->p_disc_db = NULL;
    }
}