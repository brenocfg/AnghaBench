#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int select; int mask; char* description; } ;
struct TYPE_3__ {int select; char* description; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * stdout ; 
 TYPE_2__* xtensa_perfmon_masks_table ; 
 TYPE_1__* xtensa_perfmon_select_table ; 

void xtensa_perfmon_view_cb(void *params, uint32_t select, uint32_t mask, uint32_t value)
{
    FILE *handle;
    if (params != NULL) {
        handle = (FILE *)params;
    } else {
        handle = stdout;
    }
    for (int i = 0 ; xtensa_perfmon_select_table[i].select != -1; i++) {
        if (xtensa_perfmon_select_table[i].select == select) {
            fprintf(handle, "Value = %9i, select = %2i, mask = %04x.  %s.\n", value, select, mask, xtensa_perfmon_select_table[i].description);
        }
    }
    for (int i = 0 ; xtensa_perfmon_masks_table[i].select != -1; i++) {
        if ((xtensa_perfmon_masks_table[i].select == select) && (xtensa_perfmon_masks_table[i].mask & mask)) {
            fprintf(handle, "                  %s\n", xtensa_perfmon_masks_table[i].description);
        }
    }
}