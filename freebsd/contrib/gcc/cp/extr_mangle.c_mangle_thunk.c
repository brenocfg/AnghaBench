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

/* Variables and functions */
 int /*<<< orphan*/  BINFO_VPTR_FIELD (int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUG_MANGLE ; 
 int /*<<< orphan*/  DECL_THUNK_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  THUNK_FIXED_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THUNK_TARGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THUNK_VIRTUAL_OFFSET (int /*<<< orphan*/ ) ; 
 char* finish_mangling (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  get_identifier_nocopy (char const*) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  mangle_call_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 

tree
mangle_thunk (tree fn_decl, const int this_adjusting, tree fixed_offset,
	      tree virtual_offset)
{
  const char *result;

  start_mangling (fn_decl, /*ident_p=*/true);

  write_string ("_Z");
  write_char ('T');

  if (!this_adjusting)
    {
      /* Covariant thunk with no this adjustment */
      write_char ('c');
      mangle_call_offset (integer_zero_node, NULL_TREE);
      mangle_call_offset (fixed_offset, virtual_offset);
    }
  else if (!DECL_THUNK_P (fn_decl))
    /* Plain this adjusting thunk.  */
    mangle_call_offset (fixed_offset, virtual_offset);
  else
    {
      /* This adjusting thunk to covariant thunk.  */
      write_char ('c');
      mangle_call_offset (fixed_offset, virtual_offset);
      fixed_offset = ssize_int (THUNK_FIXED_OFFSET (fn_decl));
      virtual_offset = THUNK_VIRTUAL_OFFSET (fn_decl);
      if (virtual_offset)
	virtual_offset = BINFO_VPTR_FIELD (virtual_offset);
      mangle_call_offset (fixed_offset, virtual_offset);
      fn_decl = THUNK_TARGET (fn_decl);
    }

  /* Scoped name.  */
  write_encoding (fn_decl);

  result = finish_mangling (/*warn=*/false);
  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_thunk = %s\n\n", result);
  return get_identifier_nocopy (result);
}