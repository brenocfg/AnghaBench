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
struct work_stuff {int dummy; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 scalar_t__ ARM_DEMANGLING ; 
 scalar_t__ EDG_DEMANGLING ; 
 scalar_t__ HP_DEMANGLING ; 
 scalar_t__ LUCID_DEMANGLING ; 
 int /*<<< orphan*/  delete_work_stuff (struct work_stuff*) ; 
 int /*<<< orphan*/  demangle_function_name (struct work_stuff*,char const**,int /*<<< orphan*/ *,char const*) ; 
 int demangle_signature (struct work_stuff*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct work_stuff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_appends (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  work_stuff_copy_to_from (struct work_stuff*,struct work_stuff*) ; 

__attribute__((used)) static int
iterate_demangle_function (struct work_stuff *work, const char **mangled,
                           string *declp, const char *scan)
{
  const char *mangle_init = *mangled;
  int success = 0;
  string decl_init;
  struct work_stuff work_init;

  if (*(scan + 2) == '\0')
    return 0;

  /* Do not iterate for some demangling modes, or if there's only one
     "__"-sequence.  This is the normal case.  */
  if (ARM_DEMANGLING || LUCID_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING
      || strstr (scan + 2, "__") == NULL)
    {
      demangle_function_name (work, mangled, declp, scan);
      return 1;
    }

  /* Save state so we can restart if the guess at the correct "__" was
     wrong.  */
  string_init (&decl_init);
  string_appends (&decl_init, declp);
  memset (&work_init, 0, sizeof work_init);
  work_stuff_copy_to_from (&work_init, work);

  /* Iterate over occurrences of __, allowing names and types to have a
     "__" sequence in them.  We must start with the first (not the last)
     occurrence, since "__" most often occur between independent mangled
     parts, hence starting at the last occurence inside a signature
     might get us a "successful" demangling of the signature.  */

  while (scan[2])
    {
      demangle_function_name (work, mangled, declp, scan);
      success = demangle_signature (work, mangled, declp);
      if (success)
	break;

      /* Reset demangle state for the next round.  */
      *mangled = mangle_init;
      string_clear (declp);
      string_appends (declp, &decl_init);
      work_stuff_copy_to_from (work, &work_init);

      /* Leave this underscore-sequence.  */
      scan += 2;

      /* Scan for the next "__" sequence.  */
      while (*scan && (scan[0] != '_' || scan[1] != '_'))
	scan++;

      /* Move to last "__" in this sequence.  */
      while (*scan && *scan == '_')
	scan++;
      scan -= 2;
    }

  /* Delete saved state.  */
  delete_work_stuff (&work_init);
  string_delete (&decl_init);

  return success;
}