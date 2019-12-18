#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_6__ {scalar_t__ param; scalar_t__ wanted_type; int arg_num; int pointer_count; int /*<<< orphan*/  wanted_type_name; int /*<<< orphan*/  name; scalar_t__ char_lenient_flag; scalar_t__ writing_in_flag; scalar_t__ reading_from_flag; struct TYPE_6__* next; } ;
typedef  TYPE_2__ format_wanted_type ;
struct TYPE_5__ {scalar_t__ (* type_promotes_to ) (scalar_t__) ;} ;
struct TYPE_7__ {scalar_t__ (* types_compatible_p ) (scalar_t__,scalar_t__) ;TYPE_1__ types; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ CONSTANT_CLASS_P (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  OPT_Wformat ; 
 scalar_t__ POINTER_TYPE ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_READONLY (scalar_t__) ; 
 scalar_t__ TYPE_RESTRICT (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ TYPE_VOLATILE (scalar_t__) ; 
 scalar_t__ c_common_signed_type (scalar_t__) ; 
 scalar_t__ c_common_unsigned_type (scalar_t__) ; 
 scalar_t__ char_type_node ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  format_type_warning (int /*<<< orphan*/ ,char const*,int,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 TYPE_3__ lang_hooks ; 
 scalar_t__ pedantic ; 
 scalar_t__ signed_char_type_node ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__) ; 
 scalar_t__ unsigned_char_type_node ; 
 scalar_t__ void_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
check_format_types (format_wanted_type *types, const char *format_start,
		    int format_length)
{
  for (; types != 0; types = types->next)
    {
      tree cur_param;
      tree cur_type;
      tree orig_cur_type;
      tree wanted_type;
      int arg_num;
      int i;
      int char_type_flag;
      cur_param = types->param;
      cur_type = TREE_TYPE (cur_param);
      if (cur_type == error_mark_node)
	continue;
      orig_cur_type = cur_type;
      char_type_flag = 0;
      wanted_type = types->wanted_type;
      arg_num = types->arg_num;

      /* The following should not occur here.  */
      gcc_assert (wanted_type);
      gcc_assert (wanted_type != void_type_node || types->pointer_count);

      if (types->pointer_count == 0)
	wanted_type = lang_hooks.types.type_promotes_to (wanted_type);

      wanted_type = TYPE_MAIN_VARIANT (wanted_type);

      STRIP_NOPS (cur_param);

      /* Check the types of any additional pointer arguments
	 that precede the "real" argument.  */
      for (i = 0; i < types->pointer_count; ++i)
	{
	  if (TREE_CODE (cur_type) == POINTER_TYPE)
	    {
	      cur_type = TREE_TYPE (cur_type);
	      if (cur_type == error_mark_node)
		break;

	      /* Check for writing through a NULL pointer.  */
	      if (types->writing_in_flag
		  && i == 0
		  && cur_param != 0
		  && integer_zerop (cur_param))
		warning (OPT_Wformat, "writing through null pointer "
			 "(argument %d)", arg_num);

	      /* Check for reading through a NULL pointer.  */
	      if (types->reading_from_flag
		  && i == 0
		  && cur_param != 0
		  && integer_zerop (cur_param))
		warning (OPT_Wformat, "reading through null pointer "
			 "(argument %d)", arg_num);

	      if (cur_param != 0 && TREE_CODE (cur_param) == ADDR_EXPR)
		cur_param = TREE_OPERAND (cur_param, 0);
	      else
		cur_param = 0;

	      /* See if this is an attempt to write into a const type with
		 scanf or with printf "%n".  Note: the writing in happens
		 at the first indirection only, if for example
		 void * const * is passed to scanf %p; passing
		 const void ** is simply passing an incompatible type.  */
	      if (types->writing_in_flag
		  && i == 0
		  && (TYPE_READONLY (cur_type)
		      || (cur_param != 0
			  && (CONSTANT_CLASS_P (cur_param)
			      || (DECL_P (cur_param)
				  && TREE_READONLY (cur_param))))))
		warning (OPT_Wformat, "writing into constant object "
			 "(argument %d)", arg_num);

	      /* If there are extra type qualifiers beyond the first
		 indirection, then this makes the types technically
		 incompatible.  */
	      if (i > 0
		  && pedantic
		  && (TYPE_READONLY (cur_type)
		      || TYPE_VOLATILE (cur_type)
		      || TYPE_RESTRICT (cur_type)))
		warning (OPT_Wformat, "extra type qualifiers in format "
			 "argument (argument %d)",
			 arg_num);

	    }
	  else
	    {
	      format_type_warning (types->name, format_start, format_length,
				   wanted_type, types->pointer_count,
				   types->wanted_type_name, orig_cur_type,
				   arg_num);
	      break;
	    }
	}

      if (i < types->pointer_count)
	continue;

      cur_type = TYPE_MAIN_VARIANT (cur_type);

      /* Check whether the argument type is a character type.  This leniency
	 only applies to certain formats, flagged with 'c'.
      */
      if (types->char_lenient_flag)
	char_type_flag = (cur_type == char_type_node
			  || cur_type == signed_char_type_node
			  || cur_type == unsigned_char_type_node);

      /* Check the type of the "real" argument, if there's a type we want.  */
      if (lang_hooks.types_compatible_p (wanted_type, cur_type))
	continue;
      /* If we want 'void *', allow any pointer type.
	 (Anything else would already have got a warning.)
	 With -pedantic, only allow pointers to void and to character
	 types.  */
      if (wanted_type == void_type_node
	  && (!pedantic || (i == 1 && char_type_flag)))
	continue;
      /* Don't warn about differences merely in signedness, unless
	 -pedantic.  With -pedantic, warn if the type is a pointer
	 target and not a character type, and for character types at
	 a second level of indirection.  */
      if (TREE_CODE (wanted_type) == INTEGER_TYPE
	  && TREE_CODE (cur_type) == INTEGER_TYPE
	  && (!pedantic || i == 0 || (i == 1 && char_type_flag))
	  && (TYPE_UNSIGNED (wanted_type)
	      ? wanted_type == c_common_unsigned_type (cur_type)
	      : wanted_type == c_common_signed_type (cur_type)))
	continue;
      /* Likewise, "signed char", "unsigned char" and "char" are
	 equivalent but the above test won't consider them equivalent.  */
      if (wanted_type == char_type_node
	  && (!pedantic || i < 2)
	  && char_type_flag)
	continue;
      /* Now we have a type mismatch.  */
      format_type_warning (types->name, format_start, format_length,
			   wanted_type, types->pointer_count,
			   types->wanted_type_name, orig_cur_type, arg_num);
    }
}