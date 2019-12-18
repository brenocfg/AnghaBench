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
typedef  int int32_t ;
typedef  int /*<<< orphan*/ * _bi_consumer_fn_t ;

/* Variables and functions */
#define  TSDB_BINARY_OP_ADD 132 
#define  TSDB_BINARY_OP_DIVIDE 131 
#define  TSDB_BINARY_OP_MULTIPLY 130 
#define  TSDB_BINARY_OP_REMAINDER 129 
#define  TSDB_BINARY_OP_SUBTRACT 128 
 int /*<<< orphan*/ *** add_function_arraylist ; 
 int /*<<< orphan*/ *** div_function_arraylist ; 
 int /*<<< orphan*/ *** multi_function_arraylist ; 
 int /*<<< orphan*/ *** rem_function_arraylist ; 
 int /*<<< orphan*/ *** sub_function_arraylist ; 

_bi_consumer_fn_t tGetBiConsumerFn(int32_t leftType, int32_t rightType, int32_t optr) {
  switch (optr) {
    case TSDB_BINARY_OP_ADD:
      return add_function_arraylist[leftType][rightType];
    case TSDB_BINARY_OP_SUBTRACT:
      return sub_function_arraylist[leftType][rightType];
    case TSDB_BINARY_OP_MULTIPLY:
      return multi_function_arraylist[leftType][rightType];
    case TSDB_BINARY_OP_DIVIDE:
      return div_function_arraylist[leftType][rightType];
    case TSDB_BINARY_OP_REMAINDER:
      return rem_function_arraylist[leftType][rightType];
    default:
      return NULL;
  }
  return NULL;
}