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
struct stab_types {int dummy; } ;
struct stab_handle {char* so_string; scalar_t__ so_value; char* main_filename; int gcc_compiled; scalar_t__ file_start_offset; int files; scalar_t__ function_start_offset; scalar_t__ function_end; void* n_opt_found; void* within_function; scalar_t__ sections; int /*<<< orphan*/  block_depth; struct stab_types** file_types; } ;
typedef  scalar_t__ bfd_vma ;
typedef  void* bfd_boolean ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char const*) ; 
#define  N_BCOMM 145 
#define  N_BINCL 144 
#define  N_ECOMM 143 
#define  N_EINCL 142 
#define  N_ENDM 141 
#define  N_EXCL 140 
#define  N_FN 139 
#define  N_FN_SEQ 138 
#define  N_FUN 137 
#define  N_LBRAC 136 
#define  N_MAIN 135 
#define  N_OBJ 134 
#define  N_OPT 133 
#define  N_RBRAC 132 
#define  N_SLINE 131 
#define  N_SO 130 
#define  N_SOL 129 
#define  N_WARNING 128 
 void* TRUE ; 
 char* _ (char*) ; 
 char* concat (char*,char const*,char const*) ; 
 int /*<<< orphan*/  debug_end_block (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_end_common_block (void*,char const*) ; 
 int /*<<< orphan*/  debug_end_function (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_record_line (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  debug_set_filename (void*,char*) ; 
 int /*<<< orphan*/  debug_start_block (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_start_common_block (void*,char const*) ; 
 int /*<<< orphan*/  debug_start_source (void*,char const*) ; 
 int /*<<< orphan*/  find_excl (struct stab_handle*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  parse_stab_string (void*,struct stab_handle*,int,int,scalar_t__,char const*) ; 
 char const* pop_bincl (struct stab_handle*) ; 
 int /*<<< orphan*/  push_bincl (struct stab_handle*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  stab_emit_pending_vars (void*,struct stab_handle*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ xmalloc (int) ; 
 void* xstrdup (char const*) ; 

bfd_boolean
parse_stab (void *dhandle, void *handle, int type, int desc, bfd_vma value,
	    const char *string)
{
  struct stab_handle *info = (struct stab_handle *) handle;

  /* gcc will emit two N_SO strings per compilation unit, one for the
     directory name and one for the file name.  We just collect N_SO
     strings as we see them, and start the new compilation unit when
     we see a non N_SO symbol.  */
  if (info->so_string != NULL
      && (type != N_SO || *string == '\0' || value != info->so_value))
    {
      if (! debug_set_filename (dhandle, info->so_string))
	return FALSE;
      info->main_filename = info->so_string;

      info->gcc_compiled = 0;
      info->n_opt_found = FALSE;

      /* Generally, for stabs in the symbol table, the N_LBRAC and
	 N_RBRAC symbols are relative to the N_SO symbol value.  */
      if (! info->sections)
	info->file_start_offset = info->so_value;

      /* We need to reset the mapping from type numbers to types.  We
	 can't free the old mapping, because of the use of
	 debug_make_indirect_type.  */
      info->files = 1;
      info->file_types = ((struct stab_types **)
			  xmalloc (sizeof *info->file_types));
      info->file_types[0] = NULL;

      info->so_string = NULL;

      /* Now process whatever type we just got.  */
    }

  switch (type)
    {
    case N_FN:
    case N_FN_SEQ:
      break;

    case N_LBRAC:
      /* Ignore extra outermost context from SunPRO cc and acc.  */
      if (info->n_opt_found && desc == 1)
	break;

      if (! info->within_function)
	{
	  fprintf (stderr, _("N_LBRAC not within function\n"));
	  return FALSE;
	}

      /* Start an inner lexical block.  */
      if (! debug_start_block (dhandle,
			       (value
				+ info->file_start_offset
				+ info->function_start_offset)))
	return FALSE;

      /* Emit any pending variable definitions.  */
      if (! stab_emit_pending_vars (dhandle, info))
	return FALSE;

      ++info->block_depth;
      break;

    case N_RBRAC:
      /* Ignore extra outermost context from SunPRO cc and acc.  */
      if (info->n_opt_found && desc == 1)
	break;

      /* We shouldn't have any pending variable definitions here, but,
         if we do, we probably need to emit them before closing the
         block.  */
      if (! stab_emit_pending_vars (dhandle, info))
	return FALSE;

      /* End an inner lexical block.  */
      if (! debug_end_block (dhandle,
			     (value
			      + info->file_start_offset
			      + info->function_start_offset)))
	return FALSE;

      --info->block_depth;
      if (info->block_depth < 0)
	{
	  fprintf (stderr, _("Too many N_RBRACs\n"));
	  return FALSE;
	}
      break;

    case N_SO:
      /* This always ends a function.  */
      if (info->within_function)
	{
	  bfd_vma endval;

	  endval = value;
	  if (*string != '\0'
	      && info->function_end != (bfd_vma) -1
	      && info->function_end < endval)
	    endval = info->function_end;
	  if (! stab_emit_pending_vars (dhandle, info)
	      || ! debug_end_function (dhandle, endval))
	    return FALSE;
	  info->within_function = FALSE;
	  info->function_end = (bfd_vma) -1;
	}

      /* An empty string is emitted by gcc at the end of a compilation
         unit.  */
      if (*string == '\0')
	return TRUE;

      /* Just accumulate strings until we see a non N_SO symbol.  If
         the string starts with a directory separator or some other
	 form of absolute path specification, we discard the previously
         accumulated strings.  */
      if (info->so_string == NULL)
	info->so_string = xstrdup (string);
      else
	{
	  char *f;

	  f = info->so_string;

	  if (IS_ABSOLUTE_PATH (string))
	    info->so_string = xstrdup (string);
	  else
	    info->so_string = concat (info->so_string, string,
				      (const char *) NULL);
	  free (f);
	}

      info->so_value = value;

      break;

    case N_SOL:
      /* Start an include file.  */
      if (! debug_start_source (dhandle, string))
	return FALSE;
      break;

    case N_BINCL:
      /* Start an include file which may be replaced.  */
      push_bincl (info, string, value);
      if (! debug_start_source (dhandle, string))
	return FALSE;
      break;

    case N_EINCL:
      /* End an N_BINCL include.  */
      if (! debug_start_source (dhandle, pop_bincl (info)))
	return FALSE;
      break;

    case N_EXCL:
      /* This is a duplicate of a header file named by N_BINCL which
         was eliminated by the linker.  */
      if (! find_excl (info, string, value))
	return FALSE;
      break;

    case N_SLINE:
      if (! debug_record_line (dhandle, desc,
			       value + (info->within_function
					? info->function_start_offset : 0)))
	return FALSE;
      break;

    case N_BCOMM:
      if (! debug_start_common_block (dhandle, string))
	return FALSE;
      break;

    case N_ECOMM:
      if (! debug_end_common_block (dhandle, string))
	return FALSE;
      break;

    case N_FUN:
      if (*string == '\0')
	{
	  if (info->within_function)
	    {
	      /* This always marks the end of a function; we don't
                 need to worry about info->function_end.  */
	      if (info->sections)
		value += info->function_start_offset;
	      if (! stab_emit_pending_vars (dhandle, info)
		  || ! debug_end_function (dhandle, value))
		return FALSE;
	      info->within_function = FALSE;
	      info->function_end = (bfd_vma) -1;
	    }
	  break;
	}

      /* A const static symbol in the .text section will have an N_FUN
         entry.  We need to use these to mark the end of the function,
         in case we are looking at gcc output before it was changed to
         always emit an empty N_FUN.  We can't call debug_end_function
         here, because it might be a local static symbol.  */
      if (info->within_function
	  && (info->function_end == (bfd_vma) -1
	      || value < info->function_end))
	info->function_end = value;

      /* Fall through.  */
      /* FIXME: gdb checks the string for N_STSYM, N_LCSYM or N_ROSYM
         symbols, and if it does not start with :S, gdb relocates the
         value to the start of the section.  gcc always seems to use
         :S, so we don't worry about this.  */
      /* Fall through.  */
    default:
      {
	const char *colon;

	colon = strchr (string, ':');
	if (colon != NULL
	    && (colon[1] == 'f' || colon[1] == 'F'))
	  {
	    if (info->within_function)
	      {
		bfd_vma endval;

		endval = value;
		if (info->function_end != (bfd_vma) -1
		    && info->function_end < endval)
		  endval = info->function_end;
		if (! stab_emit_pending_vars (dhandle, info)
		    || ! debug_end_function (dhandle, endval))
		  return FALSE;
		info->function_end = (bfd_vma) -1;
	      }
	    /* For stabs in sections, line numbers and block addresses
               are offsets from the start of the function.  */
	    if (info->sections)
	      info->function_start_offset = value;
	    info->within_function = TRUE;
	  }

	if (! parse_stab_string (dhandle, info, type, desc, value, string))
	  return FALSE;
      }
      break;

    case N_OPT:
      if (string != NULL && strcmp (string, "gcc2_compiled.") == 0)
	info->gcc_compiled = 2;
      else if (string != NULL && strcmp (string, "gcc_compiled.") == 0)
	info->gcc_compiled = 1;
      else
	info->n_opt_found = TRUE;
      break;

    case N_OBJ:
    case N_ENDM:
    case N_MAIN:
    case N_WARNING:
      break;
    }

  return TRUE;
}