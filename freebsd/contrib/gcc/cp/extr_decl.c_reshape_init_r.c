#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_9__ {TYPE_1__* cur; } ;
typedef  TYPE_2__ reshape_iter ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 int BRACE_ENCLOSED_INITIALIZER_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPOUND_LITERAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTRUCTOR ; 
 int /*<<< orphan*/  CONSTRUCTOR_ELTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  OPT_Wmissing_braces ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 
 TYPE_7__* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ can_convert_arg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ char_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor_elt ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  reshape_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reshape_init_array (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  reshape_init_class (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  reshape_init_vector (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
reshape_init_r (tree type, reshape_iter *d, bool first_initializer_p)
{
  tree init = d->cur->value;

  /* A non-aggregate type is always initialized with a single
     initializer.  */
  if (!CP_AGGREGATE_TYPE_P (type))
    {
      /* It is invalid to initialize a non-aggregate type with a
	 brace-enclosed initializer.
	 We need to check for BRACE_ENCLOSED_INITIALIZER_P here because
	 of g++.old-deja/g++.mike/p7626.C: a pointer-to-member constant is
	 a CONSTRUCTOR (with a record type).  */
      if (TREE_CODE (init) == CONSTRUCTOR
	  && BRACE_ENCLOSED_INITIALIZER_P (init))  /* p7626.C */
	{
	  error ("braces around scalar initializer for type %qT", type);
	  init = error_mark_node;
	}

      d->cur++;
      return init;
    }

  /* [dcl.init.aggr]

     All implicit type conversions (clause _conv_) are considered when
     initializing the aggregate member with an initializer from an
     initializer-list.  If the initializer can initialize a member,
     the member is initialized.  Otherwise, if the member is itself a
     non-empty subaggregate, brace elision is assumed and the
     initializer is considered for the initialization of the first
     member of the subaggregate.  */
  if (TREE_CODE (init) != CONSTRUCTOR
      && can_convert_arg (type, TREE_TYPE (init), init, LOOKUP_NORMAL))
    {
      d->cur++;
      return init;
    }

  /* [dcl.init.string]

      A char array (whether plain char, signed char, or unsigned char)
      can be initialized by a string-literal (optionally enclosed in
      braces); a wchar_t array can be initialized by a wide
      string-literal (optionally enclosed in braces).  */
  if (TREE_CODE (type) == ARRAY_TYPE
      && char_type_p (TYPE_MAIN_VARIANT (TREE_TYPE (type))))
    {
      tree str_init = init;

      /* Strip one level of braces if and only if they enclose a single
	 element (as allowed by [dcl.init.string]).  */
      if (!first_initializer_p
	  && TREE_CODE (str_init) == CONSTRUCTOR
	  && VEC_length (constructor_elt, CONSTRUCTOR_ELTS (str_init)) == 1)
	{
	  str_init = VEC_index (constructor_elt,
				CONSTRUCTOR_ELTS (str_init), 0)->value;
	}

      /* If it's a string literal, then it's the initializer for the array
	 as a whole. Otherwise, continue with normal initialization for
	 array types (one value per array element).  */
      if (TREE_CODE (str_init) == STRING_CST)
	{
	  d->cur++;
	  return str_init;
	}
    }

  /* The following cases are about aggregates. If we are not within a full
     initializer already, and there is not a CONSTRUCTOR, it means that there
     is a missing set of braces (that is, we are processing the case for
     which reshape_init exists).  */
  if (!first_initializer_p)
    {
      if (TREE_CODE (init) == CONSTRUCTOR)
	{
	  if (TREE_TYPE (init) && TYPE_PTRMEMFUNC_P (TREE_TYPE (init)))
	    /* There is no need to reshape pointer-to-member function
	       initializers, as they are always constructed correctly
	       by the front end.  */
           ;
	  else if (COMPOUND_LITERAL_P (init))
	  /* For a nested compound literal, there is no need to reshape since
	     brace elision is not allowed. Even if we decided to allow it,
	     we should add a call to reshape_init in finish_compound_literal,
	     before calling digest_init, so changing this code would still
	     not be necessary.  */
	    gcc_assert (!BRACE_ENCLOSED_INITIALIZER_P (init));
	  else
	    {
	      ++d->cur;
	      gcc_assert (BRACE_ENCLOSED_INITIALIZER_P (init));
	      return reshape_init (type, init);
	    }
	}

      warning (OPT_Wmissing_braces, "missing braces around initializer for %qT",
	       type);
    }

  /* Dispatch to specialized routines.  */
  if (CLASS_TYPE_P (type))
    return reshape_init_class (type, d, first_initializer_p);
  else if (TREE_CODE (type) == ARRAY_TYPE)
    return reshape_init_array (type, d);
  else if (TREE_CODE (type) == VECTOR_TYPE)
    return reshape_init_vector (type, d);
  else
    gcc_unreachable();
}