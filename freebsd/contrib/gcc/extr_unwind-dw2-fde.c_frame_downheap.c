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
typedef  scalar_t__ (* fde_compare_t ) (struct object*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;
typedef  int /*<<< orphan*/  fde ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
frame_downheap (struct object *ob, fde_compare_t fde_compare, const fde **a,
		int lo, int hi)
{
  int i, j;

  for (i = lo, j = 2*i+1;
       j < hi;
       j = 2*i+1)
    {
      if (j+1 < hi && fde_compare (ob, a[j], a[j+1]) < 0)
	++j;

      if (fde_compare (ob, a[i], a[j]) < 0)
	{
	  SWAP (a[i], a[j]);
	  i = j;
	}
      else
	break;
    }
}