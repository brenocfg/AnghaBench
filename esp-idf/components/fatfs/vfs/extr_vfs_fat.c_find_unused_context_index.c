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
 size_t FF_VOLUMES ; 
 int /*<<< orphan*/ * s_fat_ctxs ; 

__attribute__((used)) static size_t find_unused_context_index(void)
{
    for(size_t i=0; i<FF_VOLUMES; i++) {
        if (!s_fat_ctxs[i]) {
            return i;
        }
    }
    return FF_VOLUMES;
}