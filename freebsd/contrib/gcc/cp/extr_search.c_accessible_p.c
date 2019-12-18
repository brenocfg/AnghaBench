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
typedef  scalar_t__ access_kind ;

/* Variables and functions */
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ DECL_THUNK_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_P (scalar_t__) ; 
 scalar_t__ access_in_type (scalar_t__,scalar_t__) ; 
 scalar_t__ ak_protected ; 
 scalar_t__ ak_public ; 
 scalar_t__ context_for_name_lookup (scalar_t__) ; 
 scalar_t__ current_class_type ; 
 scalar_t__ current_scope () ; 
 int /*<<< orphan*/  dfs_accessible_post ; 
 scalar_t__ dfs_walk_once_accessible (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int friend_accessible_p (scalar_t__,scalar_t__,scalar_t__) ; 
 int processing_template_decl ; 
 int /*<<< orphan*/  processing_template_parmlist ; 
 int protected_accessible_p (scalar_t__,scalar_t__,scalar_t__) ; 

int
accessible_p (tree type, tree decl, bool consider_local_p)
{
  tree binfo;
  tree scope;
  access_kind access;

  /* Nonzero if it's OK to access DECL if it has protected
     accessibility in TYPE.  */
  int protected_ok = 0;

  /* If this declaration is in a block or namespace scope, there's no
     access control.  */
  if (!TYPE_P (context_for_name_lookup (decl)))
    return 1;

  /* There is no need to perform access checks inside a thunk.  */
  scope = current_scope ();
  if (scope && DECL_THUNK_P (scope))
    return 1;

  /* In a template declaration, we cannot be sure whether the
     particular specialization that is instantiated will be a friend
     or not.  Therefore, all access checks are deferred until
     instantiation.  However, PROCESSING_TEMPLATE_DECL is set in the
     parameter list for a template (because we may see dependent types
     in default arguments for template parameters), and access
     checking should be performed in the outermost parameter list.  */
  if (processing_template_decl
      && (!processing_template_parmlist || processing_template_decl > 1))
    return 1;

  if (!TYPE_P (type))
    {
      binfo = type;
      type = BINFO_TYPE (type);
    }
  else
    binfo = TYPE_BINFO (type);

  /* [class.access.base]

     A member m is accessible when named in class N if

     --m as a member of N is public, or

     --m as a member of N is private, and the reference occurs in a
       member or friend of class N, or

     --m as a member of N is protected, and the reference occurs in a
       member or friend of class N, or in a member or friend of a
       class P derived from N, where m as a member of P is private or
       protected, or

     --there exists a base class B of N that is accessible at the point
       of reference, and m is accessible when named in class B.

    We walk the base class hierarchy, checking these conditions.  */

  if (consider_local_p)
    {
      /* Figure out where the reference is occurring.  Check to see if
	 DECL is private or protected in this scope, since that will
	 determine whether protected access is allowed.  */
      if (current_class_type)
	protected_ok = protected_accessible_p (decl,
					       current_class_type, binfo);

      /* Now, loop through the classes of which we are a friend.  */
      if (!protected_ok)
	protected_ok = friend_accessible_p (scope, decl, binfo);
    }

  /* Standardize the binfo that access_in_type will use.  We don't
     need to know what path was chosen from this point onwards.  */
  binfo = TYPE_BINFO (type);

  /* Compute the accessibility of DECL in the class hierarchy
     dominated by type.  */
  access = access_in_type (type, decl);
  if (access == ak_public
      || (access == ak_protected && protected_ok))
    return 1;

  if (!consider_local_p)
    return 0;

  /* Walk the hierarchy again, looking for a base class that allows
     access.  */
  return dfs_walk_once_accessible (binfo, /*friends=*/true,
				   NULL, dfs_accessible_post, NULL)
    != NULL_TREE;
}