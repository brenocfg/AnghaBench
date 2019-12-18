#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* bsym; } ;
typedef  TYPE_1__ symbolS ;
typedef  int flagword ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int BSF_FILE ; 
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int /*<<< orphan*/  DOLLAR_LABEL_CHAR ; 
 int /*<<< orphan*/  LOCAL_LABEL_CHAR ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 char* S_GET_NAME (TYPE_1__*) ; 
 int /*<<< orphan*/  S_IS_DEBUG (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ absolute_section ; 
 scalar_t__ bfd_get_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_local_label (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  flag_keep_locals ; 
 scalar_t__ flag_mri ; 
 scalar_t__ flag_strip_local_absolute ; 
 scalar_t__ reg_section ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strchr (char const*,int /*<<< orphan*/ ) ; 

int
S_IS_LOCAL (symbolS *s)
{
  flagword flags;
  const char *name;

  if (LOCAL_SYMBOL_CHECK (s))
    return 1;

  flags = s->bsym->flags;

  /* Sanity check.  */
  if ((flags & BSF_LOCAL) && (flags & BSF_GLOBAL))
    abort ();

  if (bfd_get_section (s->bsym) == reg_section)
    return 1;

  if (flag_strip_local_absolute
      /* Keep BSF_FILE symbols in order to allow debuggers to identify
	 the source file even when the object file is stripped.  */
      && (flags & (BSF_GLOBAL | BSF_FILE)) == 0
      && bfd_get_section (s->bsym) == absolute_section)
    return 1;

  name = S_GET_NAME (s);
  return (name != NULL
	  && ! S_IS_DEBUG (s)
	  && (strchr (name, DOLLAR_LABEL_CHAR)
	      || strchr (name, LOCAL_LABEL_CHAR)
	      || (! flag_keep_locals
		  && (bfd_is_local_label (stdoutput, s->bsym)
		      || (flag_mri
			  && name[0] == '?'
			  && name[1] == '?')))));
}