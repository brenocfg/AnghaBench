#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * gap_cb_ptr ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void GAP_Deinit(void)
{
#if GAP_DYNAMIC_MEMORY == TRUE
    if (gap_cb_ptr) {
        osi_free(gap_cb_ptr);
        gap_cb_ptr = NULL;
    }
#endif
}