#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int need_abi_warning; } ;

/* Variables and functions */
 scalar_t__ CP_DECL_CONTEXT (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_EXTERNAL_LINKAGE_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_EXTERN_C_FUNCTION_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_EXTERN_C_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_LANG_SPECIFIC (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_OVERLOADED_OPERATOR_P (int /*<<< orphan*/  const) ; 
 TYPE_1__ G ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ abi_version_at_least (int) ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  write_encoding (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_source_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 

__attribute__((used)) static void
write_mangled_name (const tree decl, bool top_level)
{
  MANGLE_TRACE_TREE ("mangled-name", decl);

  if (/* The names of `extern "C"' functions are not mangled.  */
      DECL_EXTERN_C_FUNCTION_P (decl)
      /* But overloaded operator names *are* mangled.  */
      && !DECL_OVERLOADED_OPERATOR_P (decl))
    {
    unmangled_name:;

      if (top_level)
	write_string (IDENTIFIER_POINTER (DECL_NAME (decl)));
      else
	{
	  /* The standard notes: "The <encoding> of an extern "C"
	     function is treated like global-scope data, i.e. as its
	     <source-name> without a type."  We cannot write
	     overloaded operators that way though, because it contains
	     characters invalid in assembler.  */
	  if (abi_version_at_least (2))
	    write_string ("_Z");
	  else
	    G.need_abi_warning = true;
	  write_source_name (DECL_NAME (decl));
	}
    }
  else if (TREE_CODE (decl) == VAR_DECL
	   /* The names of non-static global variables aren't mangled.  */
	   && DECL_EXTERNAL_LINKAGE_P (decl)
	   && (CP_DECL_CONTEXT (decl) == global_namespace
	       /* And neither are `extern "C"' variables.  */
	       || DECL_EXTERN_C_P (decl)))
    {
      if (top_level || abi_version_at_least (2))
	goto unmangled_name;
      else
	{
	  G.need_abi_warning = true;
	  goto mangled_name;
	}
    }
  else
    {
    mangled_name:;
      write_string ("_Z");
      write_encoding (decl);
      if (DECL_LANG_SPECIFIC (decl)
	  && (DECL_MAYBE_IN_CHARGE_DESTRUCTOR_P (decl)
	      || DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (decl)))
	/* We need a distinct mangled name for these entities, but
	   we should never actually output it.  So, we append some
	   characters the assembler won't like.  */
	write_string (" *INTERNAL* ");
    }
}