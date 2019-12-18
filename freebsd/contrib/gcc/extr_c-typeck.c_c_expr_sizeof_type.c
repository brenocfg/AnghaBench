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
typedef  scalar_t__ tree ;
struct c_type_name {int dummy; } ;
struct c_expr {int /*<<< orphan*/  original_code; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int C_TYPE_VARIABLE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_MARK ; 
 int /*<<< orphan*/  c_sizeof (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ groktypename (struct c_type_name*) ; 
 int /*<<< orphan*/  pop_maybe_used (int) ; 

struct c_expr
c_expr_sizeof_type (struct c_type_name *t)
{
  tree type;
  struct c_expr ret;
  type = groktypename (t);
  ret.value = c_sizeof (type);
  ret.original_code = ERROR_MARK;
  pop_maybe_used (type != error_mark_node
		  ? C_TYPE_VARIABLE_SIZE (type) : false);
  return ret;
}