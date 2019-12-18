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
struct _getopt_data {int __posixly_correct; int __nonoption_flags_max_len; int __nonoption_flags_len; void* __ordering; int /*<<< orphan*/ * __nextchar; int /*<<< orphan*/  optind; int /*<<< orphan*/  __last_nonopt; int /*<<< orphan*/  __first_nonopt; } ;

/* Variables and functions */
 void* PERMUTE ; 
 void* REQUIRE_ORDER ; 
 void* RETURN_IN_ORDER ; 
 char* __getopt_nonoption_flags ; 
 int __libc_argc ; 
 char* const* __libc_argv ; 
 int /*<<< orphan*/  __mempcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *
_getopt_initialize (int argc, char *const *argv, const char *optstring,
		    struct _getopt_data *d)
{
  /* Start processing options with ARGV-element 1 (since ARGV-element 0
     is the program name); the sequence of previously skipped
     non-option ARGV-elements is empty.  */

  d->__first_nonopt = d->__last_nonopt = d->optind;

  d->__nextchar = NULL;

  d->__posixly_correct = !!getenv ("POSIXLY_CORRECT");

  /* Determine how to handle the ordering of options and nonoptions.  */

  if (optstring[0] == '-')
    {
      d->__ordering = RETURN_IN_ORDER;
      ++optstring;
    }
  else if (optstring[0] == '+')
    {
      d->__ordering = REQUIRE_ORDER;
      ++optstring;
    }
  else if (d->__posixly_correct)
    d->__ordering = REQUIRE_ORDER;
  else
    d->__ordering = PERMUTE;

#if defined _LIBC && defined USE_NONOPTION_FLAGS
  if (!d->__posixly_correct
      && argc == __libc_argc && argv == __libc_argv)
    {
      if (d->__nonoption_flags_max_len == 0)
	{
	  if (__getopt_nonoption_flags == NULL
	      || __getopt_nonoption_flags[0] == '\0')
	    d->__nonoption_flags_max_len = -1;
	  else
	    {
	      const char *orig_str = __getopt_nonoption_flags;
	      int len = d->__nonoption_flags_max_len = strlen (orig_str);
	      if (d->__nonoption_flags_max_len < argc)
		d->__nonoption_flags_max_len = argc;
	      __getopt_nonoption_flags =
		(char *) malloc (d->__nonoption_flags_max_len);
	      if (__getopt_nonoption_flags == NULL)
		d->__nonoption_flags_max_len = -1;
	      else
		memset (__mempcpy (__getopt_nonoption_flags, orig_str, len),
			'\0', d->__nonoption_flags_max_len - len);
	    }
	}
      d->__nonoption_flags_len = d->__nonoption_flags_max_len;
    }
  else
    d->__nonoption_flags_len = 0;
#endif

  return optstring;
}