#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* ush ;
typedef  int ulg ;
struct TYPE_8__ {int max_code; TYPE_1__* stat_desc; TYPE_4__* dyn_tree; } ;
typedef  TYPE_2__ tree_desc ;
typedef  int intf ;
struct TYPE_9__ {int* bl_count; size_t* heap; size_t heap_max; int opt_len; int static_len; } ;
typedef  TYPE_3__ deflate_state ;
struct TYPE_10__ {int Len; size_t Dad; void* Freq; } ;
typedef  TYPE_4__ ct_data ;
struct TYPE_7__ {int* extra_bits; int extra_base; int max_length; TYPE_4__* static_tree; } ;

/* Variables and functions */
 int HEAP_SIZE ; 
 int MAX_BITS ; 
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void gen_bitlen(deflate_state *s, tree_desc *desc)
{
   ct_data *tree        = desc->dyn_tree;
   int max_code         = desc->max_code;
   const ct_data *stree = desc->stat_desc->static_tree;
   const intf *extra    = desc->stat_desc->extra_bits;
   int base             = desc->stat_desc->extra_base;
   int max_length       = desc->stat_desc->max_length;
   int h;              /* heap index */
   int n, m;           /* iterate over the tree elements */
   int bits;           /* bit length */
   int xbits;          /* extra bits */
   ush f;              /* frequency */
   int overflow = 0;   /* number of elements with bit length too large */

   for (bits = 0; bits <= MAX_BITS; bits++) s->bl_count[bits] = 0;

   /* In a first pass, compute the optimal bit lengths (which may
    * overflow in the case of the bit length tree).
    */
   tree[s->heap[s->heap_max]].Len = 0; /* root of the heap */

   for (h = s->heap_max+1; h < HEAP_SIZE; h++) {
      n = s->heap[h];
      bits = tree[tree[n].Dad].Len + 1;
      if (bits > max_length) bits = max_length, overflow++;
      tree[n].Len = (ush)bits;
      /* We overwrite tree[n].Dad which is no longer needed */

      if (n > max_code) continue; /* not a leaf node */

      s->bl_count[bits]++;
      xbits = 0;
      if (n >= base) xbits = extra[n-base];
      f = tree[n].Freq;
      s->opt_len += (ulg)f * (bits + xbits);
      if (stree) s->static_len += (ulg)f * (stree[n].Len + xbits);
   }
   if (overflow == 0) return;

   Trace((stderr,"\nbit length overflow\n"));
   /* This happens for example on obj2 and pic of the Calgary corpus */

   /* Find the first bit length which could increase: */
   do {
      bits = max_length-1;
      while (s->bl_count[bits] == 0) bits--;
      s->bl_count[bits]--;      /* move one leaf down the tree */
      s->bl_count[bits+1] += 2; /* move one overflow item as its brother */
      s->bl_count[max_length]--;
      /* The brother of the overflow item also moves one step up,
       * but this does not affect bl_count[max_length]
       */
      overflow -= 2;
   } while (overflow > 0);

   /* Now recompute all bit lengths, scanning in increasing frequency.
    * h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
    * lengths instead of fixing only the wrong ones. This idea is taken
    * from 'ar' written by Haruhiko Okumura.)
    */
   for (bits = max_length; bits != 0; bits--) {
      n = s->bl_count[bits];
      while (n != 0) {
         m = s->heap[--h];
         if (m > max_code) continue;
         if ((unsigned) tree[m].Len != (unsigned) bits) {
            Trace((stderr,"code %d bits %d->%d\n", m, tree[m].Len, bits));
            s->opt_len += ((long)bits - (long)tree[m].Len)
               *(long)tree[m].Freq;
            tree[m].Len = (ush)bits;
         }
         n--;
      }
   }
}