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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int sym; int n0; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int HNODE ; 

__attribute__((used)) static void get_tree_codes(uint32_t *bits, int16_t *lens, uint8_t *xlat,
                           Node *nodes, int node,
                           uint32_t pfx, int pl, int *pos, int no_zero_count)
{
    int s;

    s = nodes[node].sym;
    if (s != HNODE || (no_zero_count && !nodes[node].count)) {
        bits[*pos] = pfx;
        lens[*pos] = pl;
        xlat[*pos] = s;
        (*pos)++;
    } else {
        pfx <<= 1;
        pl++;
        get_tree_codes(bits, lens, xlat, nodes, nodes[node].n0, pfx, pl,
                       pos, no_zero_count);
        pfx |= 1;
        get_tree_codes(bits, lens, xlat, nodes, nodes[node].n0 + 1, pfx, pl,
                       pos, no_zero_count);
    }
}