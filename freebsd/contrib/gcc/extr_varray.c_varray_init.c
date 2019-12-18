#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* varray_type ;
struct varray_descriptor {int /*<<< orphan*/  allocated; int /*<<< orphan*/  created; } ;
typedef  enum varray_data_enum { ____Placeholder_varray_data_enum } varray_data_enum ;
struct TYPE_7__ {size_t size; scalar_t__ uses_ggc; } ;
struct TYPE_6__ {size_t num_elements; int type; char const* name; scalar_t__ elements_used; } ;

/* Variables and functions */
 scalar_t__ VARRAY_HDR_SIZE ; 
 TYPE_5__* element ; 
 TYPE_1__* ggc_alloc_cleared (scalar_t__) ; 
 struct varray_descriptor* varray_descriptor (char const*) ; 
 TYPE_1__* xcalloc (scalar_t__,int) ; 

varray_type
varray_init (size_t num_elements, enum varray_data_enum element_kind,
	     const char *name)
{
  size_t data_size = num_elements * element[element_kind].size;
  varray_type ptr;
#ifdef GATHER_STATISTICS
  struct varray_descriptor *desc = varray_descriptor (name);

  desc->created++;
  desc->allocated += data_size + VARRAY_HDR_SIZE;
#endif
  if (element[element_kind].uses_ggc)
    ptr = ggc_alloc_cleared (VARRAY_HDR_SIZE + data_size);
  else
    ptr = xcalloc (VARRAY_HDR_SIZE + data_size, 1);

  ptr->num_elements = num_elements;
  ptr->elements_used = 0;
  ptr->type = element_kind;
  ptr->name = name;
  return ptr;
}