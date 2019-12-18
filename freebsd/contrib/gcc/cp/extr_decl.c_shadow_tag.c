#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {scalar_t__ attributes; } ;
typedef  TYPE_1__ cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_tag_decl (TYPE_1__*) ; 
 int /*<<< orphan*/  class_key_or_enum_as_string (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_anon_union (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_anonymous_aggr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grokdeclarator (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ maybe_process_partial_specialization (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

tree
shadow_tag (cp_decl_specifier_seq *declspecs)
{
  tree t = check_tag_decl (declspecs);

  if (!t)
    return NULL_TREE;

  if (declspecs->attributes)
    {
      warning (0, "attribute ignored in declaration of %q+#T", t);
      warning (0, "attribute for %q+#T must follow the %qs keyword",
	       t, class_key_or_enum_as_string (t));

    }

  if (maybe_process_partial_specialization (t) == error_mark_node)
    return NULL_TREE;

  /* This is where the variables in an anonymous union are
     declared.  An anonymous union declaration looks like:
     union { ... } ;
     because there is no declarator after the union, the parser
     sends that declaration here.  */
  if (ANON_AGGR_TYPE_P (t))
    {
      fixup_anonymous_aggr (t);

      if (TYPE_FIELDS (t))
	{
	  tree decl = grokdeclarator (/*declarator=*/NULL,
				      declspecs, NORMAL, 0, NULL);
	  finish_anon_union (decl);
	}
    }

  return t;
}