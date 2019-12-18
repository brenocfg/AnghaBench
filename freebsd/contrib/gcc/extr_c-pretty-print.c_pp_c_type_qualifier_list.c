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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 int TYPE_QUALS (int /*<<< orphan*/ ) ; 
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int TYPE_QUAL_VOLATILE ; 
 scalar_t__ flag_isoc99 ; 
 int /*<<< orphan*/  pp_c_cv_qualifier (int /*<<< orphan*/ *,char*) ; 

void
pp_c_type_qualifier_list (c_pretty_printer *pp, tree t)
{
   int qualifiers;

  if (!TYPE_P (t))
    t = TREE_TYPE (t);

  qualifiers = TYPE_QUALS (t);
  if (qualifiers & TYPE_QUAL_CONST)
    pp_c_cv_qualifier (pp, "const");
  if (qualifiers & TYPE_QUAL_VOLATILE)
    pp_c_cv_qualifier (pp, "volatile");
  if (qualifiers & TYPE_QUAL_RESTRICT)
    pp_c_cv_qualifier (pp, flag_isoc99 ? "restrict" : "__restrict__");
}