#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ush ;
typedef  void* uch ;
typedef  int /*<<< orphan*/  ct_data ;
struct TYPE_10__ {int /*<<< orphan*/  extra_bits; } ;
struct TYPE_9__ {int* extra_bits; TYPE_3__* static_tree; } ;
struct TYPE_8__ {int Len; int /*<<< orphan*/  Code; } ;
struct TYPE_7__ {int* extra_bits; TYPE_1__* static_tree; } ;
struct TYPE_6__ {int Len; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 int D_CODES ; 
 int LENGTH_CODES ; 
 scalar_t__ L_CODES ; 
 int MAX_BITS ; 
 void** _dist_code ; 
 void** _length_code ; 
 int* base_dist ; 
 int* base_length ; 
 int /*<<< orphan*/  bi_reverse (unsigned int,int) ; 
 int /*<<< orphan*/  extra_blbits ; 
 int* extra_dbits ; 
 int* extra_lbits ; 
 int /*<<< orphan*/  gen_codes (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gen_trees_header () ; 
 TYPE_5__ static_bl_desc ; 
 TYPE_4__ static_d_desc ; 
 TYPE_3__* static_dtree ; 
 TYPE_2__ static_l_desc ; 
 TYPE_1__* static_ltree ; 

__attribute__((used)) static void tr_static_init(void)
{
#if defined(GEN_TREES_H) || !defined(STDC)
   static int static_init_done = 0;
   int n;        /* iterates over tree elements */
   int bits;     /* bit counter */
   int length;   /* length value */
   int codes;    /* code value */
   int dist;     /* distance index */
   ush bl_count[MAX_BITS+1];
   /* number of codes at each bit length for an optimal tree */

   if (static_init_done) return;

   /* For some embedded targets, global variables are not initialized: */
#ifdef NO_INIT_GLOBAL_POINTERS
   static_l_desc.static_tree = static_ltree;
   static_l_desc.extra_bits = extra_lbits;
   static_d_desc.static_tree = static_dtree;
   static_d_desc.extra_bits = extra_dbits;
   static_bl_desc.extra_bits = extra_blbits;
#endif

   /* Initialize the mapping length (0..255) -> length code (0..28) */
   length = 0;
   for (codes = 0; codes < LENGTH_CODES-1; codes++) {
      base_length[codes] = length;
      for (n = 0; n < (1<<extra_lbits[codes]); n++) {
         _length_code[length++] = (uch)codes;
      }
   }
   Assert (length == 256, "tr_static_init: length != 256");
   /* Note that the length 255 (match length 258) can be represented
    * in two different ways: code 284 + 5 bits or code 285, so we
    * overwrite length_code[255] to use the best encoding:
    */
   _length_code[length-1] = (uch)codes;

   /* Initialize the mapping dist (0..32K) -> dist code (0..29) */
   dist = 0;
   for (codes = 0 ; codes < 16; codes++) {
      base_dist[codes] = dist;
      for (n = 0; n < (1<<extra_dbits[codes]); n++) {
         _dist_code[dist++] = (uch)codes;
      }
   }
   Assert (dist == 256, "tr_static_init: dist != 256");
   dist >>= 7; /* from now on, all distances are divided by 128 */
   for ( ; codes < D_CODES; codes++) {
      base_dist[codes] = dist << 7;
      for (n = 0; n < (1<<(extra_dbits[codes]-7)); n++) {
         _dist_code[256 + dist++] = (uch)codes;
      }
   }
   Assert (dist == 256, "tr_static_init: 256+dist != 512");

   /* Construct the codes of the static literal tree */
   for (bits = 0; bits <= MAX_BITS; bits++) bl_count[bits] = 0;
   n = 0;
   while (n <= 143) static_ltree[n++].Len = 8, bl_count[8]++;
   while (n <= 255) static_ltree[n++].Len = 9, bl_count[9]++;
   while (n <= 279) static_ltree[n++].Len = 7, bl_count[7]++;
   while (n <= 287) static_ltree[n++].Len = 8, bl_count[8]++;
   /* Codes 286 and 287 do not exist, but we must include them in the
    * tree construction to get a canonical Huffman tree (longest code
    * all ones)
    */
   gen_codes((ct_data *)static_ltree, L_CODES+1, bl_count);

   /* The static distance tree is trivial: */
   for (n = 0; n < D_CODES; n++) {
      static_dtree[n].Len = 5;
      static_dtree[n].Code = bi_reverse((unsigned)n, 5);
   }
   static_init_done = 1;

#  ifdef GEN_TREES_H
   gen_trees_header();
#  endif
#endif /* defined(GEN_TREES_H) || !defined(STDC) */
}