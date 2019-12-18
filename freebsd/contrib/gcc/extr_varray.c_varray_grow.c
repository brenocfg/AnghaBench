#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* varray_type ;
struct varray_descriptor {size_t allocated; int /*<<< orphan*/  copied; int /*<<< orphan*/  resized; } ;
struct TYPE_12__ {size_t size; scalar_t__ uses_ggc; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vdt_c; } ;
struct TYPE_11__ {size_t num_elements; size_t type; TYPE_1__ data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ VARRAY_HDR_SIZE ; 
 TYPE_9__* element ; 
 TYPE_2__* ggc_realloc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 struct varray_descriptor* varray_descriptor (int /*<<< orphan*/ ) ; 
 TYPE_2__* xrealloc (TYPE_2__*,scalar_t__) ; 

varray_type
varray_grow (varray_type va, size_t n)
{
  size_t old_elements = va->num_elements;
  if (n != old_elements)
    {
      size_t elem_size = element[va->type].size;
      size_t old_data_size = old_elements * elem_size;
      size_t data_size = n * elem_size;
#ifdef GATHER_STATISTICS
      struct varray_descriptor *desc = varray_descriptor (va->name);
      varray_type oldva = va;

      if (data_size > old_data_size)
        desc->allocated += data_size - old_data_size;
      desc->resized ++;
#endif


      if (element[va->type].uses_ggc)
	va = ggc_realloc (va, VARRAY_HDR_SIZE + data_size);
      else
	va = xrealloc (va, VARRAY_HDR_SIZE + data_size);
      va->num_elements = n;
      if (n > old_elements)
	memset (&va->data.vdt_c[old_data_size], 0, data_size - old_data_size);
#ifdef GATHER_STATISTICS
      if (oldva != va)
        desc->copied++;
#endif
    }

  return va;
}