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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int* child; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */

__attribute__((used)) static void get_tree_codes(uint32_t *codes, Node *nodes, int idx, uint32_t pfx, int bitpos)
{
    if (idx < 256 && idx >= 0) {
        codes[idx] = pfx;
    } else if (idx >= 0) {
        get_tree_codes(codes, nodes, nodes[idx].child[0], pfx + (0 << bitpos), bitpos + 1);
        get_tree_codes(codes, nodes, nodes[idx].child[1], pfx + (1U << bitpos), bitpos + 1);
    }
}