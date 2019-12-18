#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;
struct TYPE_3__ {int /*<<< orphan*/ * (* type_for_mode ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 int BUILT_IN_ADJUST_TRAMPOLINE ; 
 size_t BUILT_IN_ALLOCA ; 
 int BUILT_IN_COMPLEX_DIV_MIN ; 
 int BUILT_IN_COMPLEX_MUL_MIN ; 
 int BUILT_IN_INIT_TRAMPOLINE ; 
 size_t BUILT_IN_MEMCMP ; 
 size_t BUILT_IN_MEMCPY ; 
 size_t BUILT_IN_MEMMOVE ; 
 size_t BUILT_IN_MEMSET ; 
 int BUILT_IN_NONLOCAL_GOTO ; 
 int BUILT_IN_PROFILE_FUNC_ENTER ; 
 int BUILT_IN_PROFILE_FUNC_EXIT ; 
 int BUILT_IN_SETJMP_DISPATCHER ; 
 int BUILT_IN_SETJMP_RECEIVER ; 
 int BUILT_IN_SETJMP_SETUP ; 
 int BUILT_IN_STACK_RESTORE ; 
 int BUILT_IN_STACK_SAVE ; 
 int ECF_CONST ; 
 int ECF_MALLOC ; 
 int ECF_NORETURN ; 
 int ECF_NOTHROW ; 
 int ECF_PURE ; 
 char* GET_MODE_NAME (int) ; 
 int MAX_MODE_COMPLEX_FLOAT ; 
 int MIN_MODE_COMPLEX_FLOAT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 char TOLOWER (char const) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** built_in_decls ; 
 char** built_in_names ; 
 char* concat (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * const_ptr_type_node ; 
 int /*<<< orphan*/ * integer_type_node ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  local_define_builtin (char*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * ptr_type_node ; 
 int /*<<< orphan*/ * size_type_node ; 
 int /*<<< orphan*/ * stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * void_list_node ; 
 int /*<<< orphan*/ * void_type_node ; 

void
build_common_builtin_nodes (void)
{
  tree tmp, ftype;

  if (built_in_decls[BUILT_IN_MEMCPY] == NULL
      || built_in_decls[BUILT_IN_MEMMOVE] == NULL)
    {
      tmp = tree_cons (NULL_TREE, size_type_node, void_list_node);
      tmp = tree_cons (NULL_TREE, const_ptr_type_node, tmp);
      tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
      ftype = build_function_type (ptr_type_node, tmp);

      if (built_in_decls[BUILT_IN_MEMCPY] == NULL)
	local_define_builtin ("__builtin_memcpy", ftype, BUILT_IN_MEMCPY,
			      "memcpy", ECF_NOTHROW);
      if (built_in_decls[BUILT_IN_MEMMOVE] == NULL)
	local_define_builtin ("__builtin_memmove", ftype, BUILT_IN_MEMMOVE,
			      "memmove", ECF_NOTHROW);
    }

  if (built_in_decls[BUILT_IN_MEMCMP] == NULL)
    {
      tmp = tree_cons (NULL_TREE, size_type_node, void_list_node);
      tmp = tree_cons (NULL_TREE, const_ptr_type_node, tmp);
      tmp = tree_cons (NULL_TREE, const_ptr_type_node, tmp);
      ftype = build_function_type (integer_type_node, tmp);
      local_define_builtin ("__builtin_memcmp", ftype, BUILT_IN_MEMCMP,
			    "memcmp", ECF_PURE | ECF_NOTHROW);
    }

  if (built_in_decls[BUILT_IN_MEMSET] == NULL)
    {
      tmp = tree_cons (NULL_TREE, size_type_node, void_list_node);
      tmp = tree_cons (NULL_TREE, integer_type_node, tmp);
      tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
      ftype = build_function_type (ptr_type_node, tmp);
      local_define_builtin ("__builtin_memset", ftype, BUILT_IN_MEMSET,
			    "memset", ECF_NOTHROW);
    }

  if (built_in_decls[BUILT_IN_ALLOCA] == NULL)
    {
      tmp = tree_cons (NULL_TREE, size_type_node, void_list_node);
      ftype = build_function_type (ptr_type_node, tmp);
      local_define_builtin ("__builtin_alloca", ftype, BUILT_IN_ALLOCA,
			    "alloca", ECF_NOTHROW | ECF_MALLOC);
    }

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
  ftype = build_function_type (void_type_node, tmp);
  local_define_builtin ("__builtin_init_trampoline", ftype,
			BUILT_IN_INIT_TRAMPOLINE,
			"__builtin_init_trampoline", ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  ftype = build_function_type (ptr_type_node, tmp);
  local_define_builtin ("__builtin_adjust_trampoline", ftype,
			BUILT_IN_ADJUST_TRAMPOLINE,
			"__builtin_adjust_trampoline",
			ECF_CONST | ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
  ftype = build_function_type (void_type_node, tmp);
  local_define_builtin ("__builtin_nonlocal_goto", ftype,
			BUILT_IN_NONLOCAL_GOTO,
			"__builtin_nonlocal_goto",
			ECF_NORETURN | ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
  ftype = build_function_type (void_type_node, tmp);
  local_define_builtin ("__builtin_setjmp_setup", ftype,
			BUILT_IN_SETJMP_SETUP,
			"__builtin_setjmp_setup", ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  ftype = build_function_type (ptr_type_node, tmp);
  local_define_builtin ("__builtin_setjmp_dispatcher", ftype,
			BUILT_IN_SETJMP_DISPATCHER,
			"__builtin_setjmp_dispatcher",
			ECF_PURE | ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  ftype = build_function_type (void_type_node, tmp);
  local_define_builtin ("__builtin_setjmp_receiver", ftype,
			BUILT_IN_SETJMP_RECEIVER,
			"__builtin_setjmp_receiver", ECF_NOTHROW);

  ftype = build_function_type (ptr_type_node, void_list_node);
  local_define_builtin ("__builtin_stack_save", ftype, BUILT_IN_STACK_SAVE,
			"__builtin_stack_save", ECF_NOTHROW);

  tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
  ftype = build_function_type (void_type_node, tmp);
  local_define_builtin ("__builtin_stack_restore", ftype,
			BUILT_IN_STACK_RESTORE,
			"__builtin_stack_restore", ECF_NOTHROW);

  ftype = build_function_type (void_type_node, void_list_node);
  local_define_builtin ("__builtin_profile_func_enter", ftype,
			BUILT_IN_PROFILE_FUNC_ENTER, "profile_func_enter", 0);
  local_define_builtin ("__builtin_profile_func_exit", ftype,
			BUILT_IN_PROFILE_FUNC_EXIT, "profile_func_exit", 0);

  /* Complex multiplication and division.  These are handled as builtins
     rather than optabs because emit_library_call_value doesn't support
     complex.  Further, we can do slightly better with folding these 
     beasties if the real and complex parts of the arguments are separate.  */
  {
    enum machine_mode mode;

    for (mode = MIN_MODE_COMPLEX_FLOAT; mode <= MAX_MODE_COMPLEX_FLOAT; ++mode)
      {
	char mode_name_buf[4], *q;
	const char *p;
	enum built_in_function mcode, dcode;
	tree type, inner_type;

	type = lang_hooks.types.type_for_mode (mode, 0);
	if (type == NULL)
	  continue;
	inner_type = TREE_TYPE (type);

	tmp = tree_cons (NULL_TREE, inner_type, void_list_node);
	tmp = tree_cons (NULL_TREE, inner_type, tmp);
	tmp = tree_cons (NULL_TREE, inner_type, tmp);
	tmp = tree_cons (NULL_TREE, inner_type, tmp);
	ftype = build_function_type (type, tmp);

        mcode = BUILT_IN_COMPLEX_MUL_MIN + mode - MIN_MODE_COMPLEX_FLOAT;
        dcode = BUILT_IN_COMPLEX_DIV_MIN + mode - MIN_MODE_COMPLEX_FLOAT;

        for (p = GET_MODE_NAME (mode), q = mode_name_buf; *p; p++, q++)
	  *q = TOLOWER (*p);
	*q = '\0';

	built_in_names[mcode] = concat ("__mul", mode_name_buf, "3", NULL);
        local_define_builtin (built_in_names[mcode], ftype, mcode,
			      built_in_names[mcode], ECF_CONST | ECF_NOTHROW);

	built_in_names[dcode] = concat ("__div", mode_name_buf, "3", NULL);
        local_define_builtin (built_in_names[dcode], ftype, dcode,
			      built_in_names[dcode], ECF_CONST | ECF_NOTHROW);
      }
  }
}