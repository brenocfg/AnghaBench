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
struct stab_handle {int dummy; } ;
struct stab_demangle_typestring {int dummy; } ;
struct stab_demangle_info {int typestring_alloc; struct stab_demangle_typestring* typestrings; int /*<<< orphan*/ * args; int /*<<< orphan*/  varargs; scalar_t__ typestring_count; struct stab_handle* info; void* dhandle; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct stab_demangle_typestring*) ; 
 int /*<<< orphan*/  stab_demangle_prefix (struct stab_demangle_info*,char const**,unsigned int) ; 
 int /*<<< orphan*/  stab_demangle_signature (struct stab_demangle_info*,char const**) ; 
 int /*<<< orphan*/ * stab_demangle_v3_argtypes (void*,struct stab_handle*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static debug_type *
stab_demangle_argtypes (void *dhandle, struct stab_handle *info,
			const char *physname, bfd_boolean *pvarargs,
			unsigned int physname_len)
{
  struct stab_demangle_info minfo;

  /* Check for the g++ V3 ABI.  */
  if (physname[0] == '_' && physname[1] == 'Z')
    return stab_demangle_v3_argtypes (dhandle, info, physname, pvarargs);

  minfo.dhandle = dhandle;
  minfo.info = info;
  minfo.args = NULL;
  minfo.varargs = FALSE;
  minfo.typestring_alloc = 10;
  minfo.typestrings = ((struct stab_demangle_typestring *)
		       xmalloc (minfo.typestring_alloc
				* sizeof *minfo.typestrings));
  minfo.typestring_count = 0;

  /* cplus_demangle checks for special GNU mangled forms, but we can't
     see any of them in mangled method argument types.  */

  if (! stab_demangle_prefix (&minfo, &physname, physname_len))
    goto error_return;

  if (*physname != '\0')
    {
      if (! stab_demangle_signature (&minfo, &physname))
	goto error_return;
    }

  free (minfo.typestrings);
  minfo.typestrings = NULL;

  if (minfo.args == NULL)
    fprintf (stderr, _("no argument types in mangled string\n"));

  *pvarargs = minfo.varargs;
  return minfo.args;

 error_return:
  if (minfo.typestrings != NULL)
    free (minfo.typestrings);
  return NULL;
}