#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bits_sent; scalar_t__ dyn_dtree; scalar_t__ dyn_ltree; TYPE_1__* bl_tree; } ;
typedef  TYPE_2__ deflate_state ;
typedef  int /*<<< orphan*/  ct_data ;
struct TYPE_6__ {int Len; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 int BL_CODES ; 
 int D_CODES ; 
 int L_CODES ; 
 int /*<<< orphan*/  Tracev (int /*<<< orphan*/ ) ; 
 size_t* bl_order ; 
 int /*<<< orphan*/  send_bits (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  send_tree (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void send_all_trees(
	deflate_state *s,
	int lcodes,  /* number of codes for each tree */
	int dcodes,  /* number of codes for each tree */
	int blcodes  /* number of codes for each tree */
)
{
    int rank;                    /* index in bl_order */

    Assert (lcodes >= 257 && dcodes >= 1 && blcodes >= 4, "not enough codes");
    Assert (lcodes <= L_CODES && dcodes <= D_CODES && blcodes <= BL_CODES,
            "too many codes");
    Tracev((stderr, "\nbl counts: "));
    send_bits(s, lcodes-257, 5); /* not +255 as stated in appnote.txt */
    send_bits(s, dcodes-1,   5);
    send_bits(s, blcodes-4,  4); /* not -3 as stated in appnote.txt */
    for (rank = 0; rank < blcodes; rank++) {
        Tracev((stderr, "\nbl code %2d ", bl_order[rank]));
        send_bits(s, s->bl_tree[bl_order[rank]].Len, 3);
    }
    Tracev((stderr, "\nbl tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes-1); /* literal tree */
    Tracev((stderr, "\nlit tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes-1); /* distance tree */
    Tracev((stderr, "\ndist tree: sent %ld", s->bits_sent));
}