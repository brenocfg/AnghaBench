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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_c_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int int_cst_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  unsigned_type_node ; 

tree
build_indirect_object_id_exp (tree exp)
{
  tree dst_obj;
  int  int_size = int_cst_value (TYPE_SIZE_UNIT (unsigned_type_node));
  int offset;
  /* dst->object In thid case 'object' is the field
   of the object passed offset by: void * + void* + int + int + void* + void *
   This must match definition of Block_byref structs. */
  /* APPLE LOCAL radar 6244520 */
  offset = GET_MODE_SIZE (Pmode) + GET_MODE_SIZE (Pmode) 
	    + int_size + int_size + GET_MODE_SIZE (Pmode) +
	    GET_MODE_SIZE (Pmode);
  dst_obj = build2 (PLUS_EXPR, ptr_type_node, exp,
		     build_int_cst (NULL_TREE, offset));
  /* APPLE LOCAL begin radar 6180456 */
  /* Type case to: 'void **' */
  dst_obj = build_c_cast (build_pointer_type (ptr_type_node), dst_obj);
  dst_obj = build_indirect_ref (dst_obj, "unary *");
  /* APPLE LOCAL end radar 6180456 */
  return dst_obj;
}