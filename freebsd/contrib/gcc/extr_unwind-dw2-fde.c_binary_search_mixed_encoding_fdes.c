#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct fde_vector* sort; } ;
struct object {TYPE_1__ u; } ;
struct fde_vector {size_t count; TYPE_2__** array; } ;
struct TYPE_6__ {unsigned char const* pc_begin; } ;
typedef  TYPE_2__ fde ;
typedef  scalar_t__ _Unwind_Ptr ;

/* Variables and functions */
 int /*<<< orphan*/  base_from_object (int,struct object*) ; 
 int get_fde_encoding (TYPE_2__ const*) ; 
 unsigned char* read_encoded_value_with_base (int,int /*<<< orphan*/ ,unsigned char const*,scalar_t__*) ; 

__attribute__((used)) static inline const fde *
binary_search_mixed_encoding_fdes (struct object *ob, void *pc)
{
  struct fde_vector *vec = ob->u.sort;
  size_t lo, hi;

  for (lo = 0, hi = vec->count; lo < hi; )
    {
      size_t i = (lo + hi) / 2;
      const fde *f = vec->array[i];
      _Unwind_Ptr pc_begin, pc_range;
      const unsigned char *p;
      int encoding;

      encoding = get_fde_encoding (f);
      p = read_encoded_value_with_base (encoding,
					base_from_object (encoding, ob),
					f->pc_begin, &pc_begin);
      read_encoded_value_with_base (encoding & 0x0F, 0, p, &pc_range);

      if ((_Unwind_Ptr) pc < pc_begin)
	hi = i;
      else if ((_Unwind_Ptr) pc >= pc_begin + pc_range)
	lo = i + 1;
      else
	return f;
    }

  return NULL;
}