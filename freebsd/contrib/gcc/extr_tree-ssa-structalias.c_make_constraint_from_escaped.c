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
typedef  TYPE_1__* varinfo_t ;
struct constraint_expr {void* type; scalar_t__ offset; int /*<<< orphan*/  var; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 void* SCALAR ; 
 int /*<<< orphan*/  escaped_vars_id ; 
 int /*<<< orphan*/  new_constraint (struct constraint_expr,struct constraint_expr) ; 
 int /*<<< orphan*/  process_constraint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_constraint_from_escaped (varinfo_t vi)
{
  struct constraint_expr lhs, rhs;
  
  lhs.var = vi->id;
  lhs.offset = 0;
  lhs.type = SCALAR;
  
  rhs.var = escaped_vars_id;
  rhs.offset = 0;
  rhs.type = SCALAR;
  process_constraint (new_constraint (lhs, rhs));
}