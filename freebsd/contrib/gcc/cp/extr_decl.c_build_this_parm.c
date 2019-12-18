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
typedef  int cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int /*<<< orphan*/  build_artificial_parm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_apply_type_quals_to_decl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_qualified_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  this_identifier ; 

tree
build_this_parm (tree type, cp_cv_quals quals)
{
  tree this_type;
  tree qual_type;
  tree parm;
  cp_cv_quals this_quals;

  this_type = TREE_VALUE (TYPE_ARG_TYPES (type));
  /* The `this' parameter is implicitly `const'; it cannot be
     assigned to.  */
  this_quals = (quals & TYPE_QUAL_RESTRICT) | TYPE_QUAL_CONST;
  qual_type = cp_build_qualified_type (this_type, this_quals);
  parm = build_artificial_parm (this_identifier, qual_type);
  cp_apply_type_quals_to_decl (this_quals, parm);
  return parm;
}