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
struct TYPE_3__ {int /*<<< orphan*/  in_use; int /*<<< orphan*/ * gap_cback; } ;
typedef  TYPE_1__ tGAP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

void gap_free_cb (tGAP_INFO *p_cb)
{
    if (p_cb) {
        p_cb->gap_cback = NULL;
        p_cb->in_use = FALSE;
    }
}