#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  base_path; } ;

/* Variables and functions */
 size_t FF_VOLUMES ; 
 TYPE_1__** s_fat_ctxs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static size_t find_context_index_by_path(const char* base_path)
{
    for(size_t i=0; i<FF_VOLUMES; i++) {
        if (s_fat_ctxs[i] && !strcmp(s_fat_ctxs[i]->base_path, base_path)) {
            return i;
        }
    }
    return FF_VOLUMES;
}