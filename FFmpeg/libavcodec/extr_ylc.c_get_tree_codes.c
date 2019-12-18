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
typedef  unsigned long long uint32_t ;
typedef  unsigned long long int16_t ;
struct TYPE_3__ {int sym; int l; int r; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 unsigned long long FFMAX (int,int) ; 

__attribute__((used)) static void get_tree_codes(uint32_t *bits, int16_t *lens, uint8_t *xlat,
                           Node *nodes, int node,
                           uint32_t pfx, int pl, int *pos)
{
    int s;

    s = nodes[node].sym;
    if (s != -1) {
        bits[*pos] = (~pfx) & ((1ULL << FFMAX(pl, 1)) - 1);
        lens[*pos] = FFMAX(pl, 1);
        xlat[*pos] = s + (pl == 0);
        (*pos)++;
    } else {
        pfx <<= 1;
        pl++;
        get_tree_codes(bits, lens, xlat, nodes, nodes[node].l, pfx, pl,
                       pos);
        pfx |= 1;
        get_tree_codes(bits, lens, xlat, nodes, nodes[node].r, pfx, pl,
                       pos);
    }
}