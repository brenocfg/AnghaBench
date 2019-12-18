#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; TYPE_1__* home_package; } ;
struct TYPE_5__ {char* path; } ;

/* Variables and functions */
 size_t buf_len (TYPE_2__**) ; 
 int /*<<< orphan*/  finalize_sym (TYPE_2__*) ; 
 scalar_t__ flag_verbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__** reachable_syms ; 

void finalize_reachable_syms(void) {
    if (flag_verbose) {
        printf("Finalizing reachable symbols\n");
    }
    size_t prev_num_reachable = 0;
    size_t num_reachable = buf_len(reachable_syms);
    for (size_t i = 0; i < num_reachable; i++) {
        finalize_sym(reachable_syms[i]);
        if (i == num_reachable - 1) {
            if (flag_verbose) {
                printf("New reachable symbols:");
                for (size_t k = prev_num_reachable; k < num_reachable; k++) {
                    printf(" %s/%s", reachable_syms[k]->home_package->path, reachable_syms[k]->name);
                }
                printf("\n");
            }
            prev_num_reachable = num_reachable;
            num_reachable = buf_len(reachable_syms);
        }
    }
}