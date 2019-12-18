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
struct type {int dummy; } ;
struct agent_expr {int dummy; } ;
typedef  enum agent_op { ____Placeholder_agent_op } agent_op ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int) ; 

__attribute__((used)) static void
gen_scale (struct agent_expr *ax, enum agent_op op, struct type *type)
{
  struct type *element = TYPE_TARGET_TYPE (type);

  if (TYPE_LENGTH (element) != 1)
    {
      ax_const_l (ax, TYPE_LENGTH (element));
      ax_simple (ax, op);
    }
}