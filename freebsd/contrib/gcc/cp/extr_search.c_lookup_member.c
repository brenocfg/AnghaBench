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
typedef  char* tree ;
struct lookup_field_info {char* type; char* name; int want_type; char* rval; char* rval_binfo; char* errstr; char* ambiguous; } ;
typedef  int /*<<< orphan*/  lfi ;

/* Variables and functions */
 char* BINFO_TYPE (char*) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (char*) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IDENTIFIER_TYPENAME_P (char*) ; 
 int /*<<< orphan*/  IS_AGGR_TYPE_CODE (scalar_t__) ; 
 char* NULL_TREE ; 
 scalar_t__ TREE_BINFO ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 char* TYPE_BINFO (char*) ; 
 char* build_baselink (char*,char*,char*,char*) ; 
 char* complete_type (char*) ; 
 int /*<<< orphan*/  dfs_walk_all (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lookup_field_info*) ; 
 int /*<<< orphan*/  error (char const*,char*,char*) ; 
 char* error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_overloaded_fn (char*) ; 
 int /*<<< orphan*/  lookup_field_r ; 
 int /*<<< orphan*/  memset (struct lookup_field_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_calls_lookup_field ; 
 int /*<<< orphan*/  perform_or_defer_access_check (char*,char*,char*) ; 
 int /*<<< orphan*/  print_candidates (char*) ; 
 int /*<<< orphan*/  really_overloaded_fn (char*) ; 

tree
lookup_member (tree xbasetype, tree name, int protect, bool want_type)
{
  tree rval, rval_binfo = NULL_TREE;
  tree type = NULL_TREE, basetype_path = NULL_TREE;
  struct lookup_field_info lfi;

  /* rval_binfo is the binfo associated with the found member, note,
     this can be set with useful information, even when rval is not
     set, because it must deal with ALL members, not just non-function
     members.  It is used for ambiguity checking and the hidden
     checks.  Whereas rval is only set if a proper (not hidden)
     non-function member is found.  */

  const char *errstr = 0;

  gcc_assert (TREE_CODE (name) == IDENTIFIER_NODE);

  if (TREE_CODE (xbasetype) == TREE_BINFO)
    {
      type = BINFO_TYPE (xbasetype);
      basetype_path = xbasetype;
    }
  else
    {
      if (!IS_AGGR_TYPE_CODE (TREE_CODE (xbasetype)))
	return NULL_TREE;
      type = xbasetype;
      xbasetype = NULL_TREE;
    }

  type = complete_type (type);
  if (!basetype_path)
    basetype_path = TYPE_BINFO (type);

  if (!basetype_path)
    return NULL_TREE;

#ifdef GATHER_STATISTICS
  n_calls_lookup_field++;
#endif /* GATHER_STATISTICS */

  memset (&lfi, 0, sizeof (lfi));
  lfi.type = type;
  lfi.name = name;
  lfi.want_type = want_type;
  dfs_walk_all (basetype_path, &lookup_field_r, NULL, &lfi);
  rval = lfi.rval;
  rval_binfo = lfi.rval_binfo;
  if (rval_binfo)
    type = BINFO_TYPE (rval_binfo);
  errstr = lfi.errstr;

  /* If we are not interested in ambiguities, don't report them;
     just return NULL_TREE.  */
  if (!protect && lfi.ambiguous)
    return NULL_TREE;

  if (protect == 2)
    {
      if (lfi.ambiguous)
	return lfi.ambiguous;
      else
	protect = 0;
    }

  /* [class.access]

     In the case of overloaded function names, access control is
     applied to the function selected by overloaded resolution.  

     We cannot check here, even if RVAL is only a single non-static
     member function, since we do not know what the "this" pointer
     will be.  For:

        class A { protected: void f(); };
        class B : public A { 
          void g(A *p) {
            f(); // OK
            p->f(); // Not OK.
          }
        };

    only the first call to "f" is valid.  However, if the function is
    static, we can check.  */
  if (rval && protect 
      && !really_overloaded_fn (rval)
      && !(TREE_CODE (rval) == FUNCTION_DECL
	   && DECL_NONSTATIC_MEMBER_FUNCTION_P (rval)))
    perform_or_defer_access_check (basetype_path, rval, rval);

  if (errstr && protect)
    {
      error (errstr, name, type);
      if (lfi.ambiguous)
	print_candidates (lfi.ambiguous);
      rval = error_mark_node;
    }

  if (rval && is_overloaded_fn (rval))
    rval = build_baselink (rval_binfo, basetype_path, rval,
			   (IDENTIFIER_TYPENAME_P (name)
			   ? TREE_TYPE (name): NULL_TREE));
  return rval;
}