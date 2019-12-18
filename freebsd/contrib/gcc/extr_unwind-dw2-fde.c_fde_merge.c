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
struct fde_vector {size_t count; int /*<<< orphan*/  const** array; } ;
typedef  scalar_t__ (* fde_compare_t ) (struct object*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;
typedef  int /*<<< orphan*/  const fde ;

/* Variables and functions */

__attribute__((used)) static inline void
fde_merge (struct object *ob, fde_compare_t fde_compare,
	   struct fde_vector *v1, struct fde_vector *v2)
{
  size_t i1, i2;
  const fde * fde2;

  i2 = v2->count;
  if (i2 > 0)
    {
      i1 = v1->count;
      do
	{
	  i2--;
	  fde2 = v2->array[i2];
	  while (i1 > 0 && fde_compare (ob, v1->array[i1-1], fde2) > 0)
	    {
	      v1->array[i1+i2] = v1->array[i1-1];
	      i1--;
	    }
	  v1->array[i1+i2] = fde2;
	}
      while (i2 > 0);
      v1->count += v2->count;
    }
}