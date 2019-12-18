#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ush ;
typedef  scalar_t__ uch ;
struct TYPE_15__ {int max_code; TYPE_1__* stat_desc; TYPE_4__* dyn_tree; } ;
typedef  TYPE_2__ tree_desc ;
struct TYPE_16__ {size_t heap_len; size_t heap_max; int* heap; scalar_t__* depth; int /*<<< orphan*/  bl_count; TYPE_4__* bl_tree; int /*<<< orphan*/  static_len; int /*<<< orphan*/  opt_len; } ;
typedef  TYPE_3__ deflate_state ;
struct TYPE_17__ {int Freq; scalar_t__ Dad; scalar_t__ Len; } ;
typedef  TYPE_4__ ct_data ;
struct TYPE_14__ {int elems; TYPE_4__* static_tree; } ;

/* Variables and functions */
 size_t HEAP_SIZE ; 
 size_t SMALLEST ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  gen_bitlen (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gen_codes (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqdownheap (TYPE_3__*,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  pqremove (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void build_tree(deflate_state *s, tree_desc *desc)
{
   ct_data *tree         = desc->dyn_tree;
   const ct_data *stree  = desc->stat_desc->static_tree;
   int elems             = desc->stat_desc->elems;
   int n, m;          /* iterate over heap elements */
   int max_code = -1; /* largest code with non zero frequency */
   int node;          /* new node being created */

   /* Construct the initial heap, with least frequent element in
    * heap[SMALLEST]. The sons of heap[n] are heap[2*n] and heap[2*n+1].
    * heap[0] is not used.
    */
   s->heap_len = 0, s->heap_max = HEAP_SIZE;

   for (n = 0; n < elems; n++) {
      if (tree[n].Freq != 0) {
         s->heap[++(s->heap_len)] = max_code = n;
         s->depth[n] = 0;
      } else {
         tree[n].Len = 0;
      }
   }

   /* The pkzip format requires that at least one distance code exists,
    * and that at least one bit should be sent even if there is only one
    * possible code. So to avoid special checks later on we force at least
    * two codes of non zero frequency.
    */
   while (s->heap_len < 2) {
      node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
      tree[node].Freq = 1;
      s->depth[node] = 0;
      s->opt_len--; if (stree) s->static_len -= stree[node].Len;
      /* node is 0 or 1 so it does not have extra bits */
   }
   desc->max_code = max_code;

   /* The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
    * establish sub-heaps of increasing lengths:
    */
   for (n = s->heap_len/2; n >= 1; n--) pqdownheap(s, tree, n);

   /* Construct the Huffman tree by repeatedly combining the least two
    * frequent nodes.
    */
   node = elems;              /* next internal node of the tree */
   do {
      pqremove(s, tree, n);  /* n = node of least frequency */
      m = s->heap[SMALLEST]; /* m = node of next least frequency */

      s->heap[--(s->heap_max)] = n; /* keep the nodes sorted by frequency */
      s->heap[--(s->heap_max)] = m;

      /* Create a new node father of n and m */
      tree[node].Freq = tree[n].Freq + tree[m].Freq;
      s->depth[node] = (uch)((s->depth[n] >= s->depth[m] ?
               s->depth[n] : s->depth[m]) + 1);
      tree[n].Dad = tree[m].Dad = (ush)node;
#ifdef DUMP_BL_TREE
      if (tree == s->bl_tree) {
         fprintf(stderr,"\nnode %d(%d), sons %d(%d) %d(%d)",
               node, tree[node].Freq, n, tree[n].Freq, m, tree[m].Freq);
      }
#endif
      /* and insert the new node in the heap */
      s->heap[SMALLEST] = node++;
      pqdownheap(s, tree, SMALLEST);

   } while (s->heap_len >= 2);

   s->heap[--(s->heap_max)] = s->heap[SMALLEST];

   /* At this point, the fields freq and dad are set. We can now
    * generate the bit lengths.
    */
   gen_bitlen(s, (tree_desc *)desc);

   /* The field len is now set, we can generate the bit codes */
   gen_codes ((ct_data *)tree, max_code, s->bl_count);
}