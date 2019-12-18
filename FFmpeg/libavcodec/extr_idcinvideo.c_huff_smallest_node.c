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
struct TYPE_3__ {int used; int count; } ;
typedef  TYPE_1__ hnode ;

/* Variables and functions */

__attribute__((used)) static int huff_smallest_node(hnode *hnodes, int num_hnodes) {
    int i;
    int best, best_node;

    best = 99999999;
    best_node = -1;
    for(i = 0; i < num_hnodes; i++) {
        if(hnodes[i].used)
            continue;
        if(!hnodes[i].count)
            continue;
        if(hnodes[i].count < best) {
            best = hnodes[i].count;
            best_node = i;
        }
    }

    if(best_node == -1)
        return -1;
    hnodes[best_node].used = 1;
    return best_node;
}