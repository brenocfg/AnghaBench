#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_desc ;
struct TYPE_9__ {int /*<<< orphan*/  max_code; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_code; } ;
struct TYPE_11__ {int opt_len; int /*<<< orphan*/  static_len; TYPE_3__* bl_tree; int /*<<< orphan*/  bl_desc; TYPE_2__ d_desc; scalar_t__ dyn_dtree; TYPE_1__ l_desc; scalar_t__ dyn_ltree; } ;
typedef  TYPE_4__ deflate_state ;
typedef  int /*<<< orphan*/  ct_data ;
struct TYPE_10__ {scalar_t__ Len; } ;

/* Variables and functions */
 int BL_CODES ; 
 int /*<<< orphan*/  Tracev (int /*<<< orphan*/ ) ; 
 size_t* bl_order ; 
 int /*<<< orphan*/  build_tree (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_tree (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int build_bl_tree(deflate_state *s)
{
   int max_blindex;  /* index of last bit length code of non zero freq */

   /* Determine the bit length frequencies for literal and distance trees */
   scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
   scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);

   /* Build the bit length tree: */
   build_tree(s, (tree_desc *)(&(s->bl_desc)));
   /* opt_len now includes the length of the tree representations, except
    * the lengths of the bit lengths codes and the 5+5+4 bits for the counts.
    */

   /* Determine the number of bit length codes to send. The pkzip format
    * requires that at least 4 bit length codes be sent. (appnote.txt says
    * 3 but the actual value used is 4.)
    */
   for (max_blindex = BL_CODES-1; max_blindex >= 3; max_blindex--) {
      if (s->bl_tree[bl_order[max_blindex]].Len != 0) break;
   }
   /* Update opt_len to include the bit length tree and counts */
   s->opt_len += 3*(max_blindex+1) + 5+5+4;
   Tracev((stderr, "\ndyn trees: dyn %ld, stat %ld",
            s->opt_len, s->static_len));

   return max_blindex;
}