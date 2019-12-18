#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct object {int dummy; } ;
struct fde_vector {size_t count; int /*<<< orphan*/ ** array; } ;
typedef  int /*<<< orphan*/  fde_compare_t ;
typedef  int /*<<< orphan*/  fde ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  frame_downheap (struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int) ; 

__attribute__((used)) static void
frame_heapsort (struct object *ob, fde_compare_t fde_compare,
		struct fde_vector *erratic)
{
  /* For a description of this algorithm, see:
     Samuel P. Harbison, Guy L. Steele Jr.: C, a reference manual, 2nd ed.,
     p. 60-61.  */
  const fde ** a = erratic->array;
  /* A portion of the array is called a "heap" if for all i>=0:
     If i and 2i+1 are valid indices, then a[i] >= a[2i+1].
     If i and 2i+2 are valid indices, then a[i] >= a[2i+2].  */
  size_t n = erratic->count;
  int m;

  /* Expand our heap incrementally from the end of the array, heapifying
     each resulting semi-heap as we go.  After each step, a[m] is the top
     of a heap.  */
  for (m = n/2-1; m >= 0; --m)
    frame_downheap (ob, fde_compare, a, m, n);

  /* Shrink our heap incrementally from the end of the array, first
     swapping out the largest element a[0] and then re-heapifying the
     resulting semi-heap.  After each step, a[0..m) is a heap.  */
  for (m = n-1; m >= 1; --m)
    {
      SWAP (a[0], a[m]);
      frame_downheap (ob, fde_compare, a, 0, m);
    }
#undef SWAP
}