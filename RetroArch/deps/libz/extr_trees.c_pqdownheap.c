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
struct TYPE_3__ {int* heap; int heap_len; int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ deflate_state ;
typedef  int /*<<< orphan*/  ct_data ;

/* Variables and functions */
 scalar_t__ smaller (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqdownheap(deflate_state *s, ct_data *tree, int k)
{
   int v = s->heap[k];
   int j = k << 1;  /* left son of k */
   while (j <= s->heap_len) {
      /* Set j to the smallest of the two sons: */
      if (j < s->heap_len &&
            smaller(tree, s->heap[j+1], s->heap[j], s->depth)) {
         j++;
      }
      /* Exit if v is smaller than both sons */
      if (smaller(tree, v, s->heap[j], s->depth)) break;

      /* Exchange v with the smallest son */
      s->heap[k] = s->heap[j];  k = j;

      /* And continue down the tree, setting j to the left son of k */
      j <<= 1;
   }
   s->heap[k] = v;
}