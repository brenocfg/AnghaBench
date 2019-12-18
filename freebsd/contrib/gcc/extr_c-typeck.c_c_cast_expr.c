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
struct c_type_name {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_c_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  groktypename (struct c_type_name*) ; 
 int warn_strict_prototypes ; 

tree
c_cast_expr (struct c_type_name *type_name, tree expr)
{
  tree type;
  int saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  if (TREE_CODE (expr) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name);
  warn_strict_prototypes = saved_wsp;

  return build_c_cast (type, expr);
}