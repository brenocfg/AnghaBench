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

/* Variables and functions */
 int /*<<< orphan*/  begin_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  note_template_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  processing_template_parmlist ; 
 int /*<<< orphan*/  sk_template_parms ; 

void
begin_template_parm_list (void)
{
  /* We use a non-tag-transparent scope here, which causes pushtag to
     put tags in this scope, rather than in the enclosing class or
     namespace scope.  This is the right thing, since we want
     TEMPLATE_DECLS, and not TYPE_DECLS for template classes.  For a
     global template class, push_template_decl handles putting the
     TEMPLATE_DECL into top-level scope.  For a nested template class,
     e.g.:

       template <class T> struct S1 {
	 template <class T> struct S2 {};
       };

     pushtag contains special code to call pushdecl_with_scope on the
     TEMPLATE_DECL for S2.  */
  begin_scope (sk_template_parms, NULL);
  ++processing_template_decl;
  ++processing_template_parmlist;
  note_template_header (0);
}