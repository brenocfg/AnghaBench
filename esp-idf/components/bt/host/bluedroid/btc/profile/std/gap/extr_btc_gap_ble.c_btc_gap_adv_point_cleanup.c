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
 int /*<<< orphan*/  osi_free (void*) ; 

__attribute__((used)) static void btc_gap_adv_point_cleanup(void **buf)
{
    if (NULL == *buf) {
        return;
    }
    osi_free(*buf);
    *buf = NULL;
}