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

/* Variables and functions */
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,scalar_t__,char*,char const*,char const*) ; 
 int /*<<< orphan*/  failed_locale_specific_sorting ; 
 int file_name_cmp (char const*,char const*) ; 
 scalar_t__ ignore_file_name_case ; 
 scalar_t__ locale_specific_sorting ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int strcasecmp (char const*,char const*) ; 
 int strcasecoll (char const*,char const*) ; 
 int strcoll (char const*,char const*) ; 

__attribute__((used)) static int
compare_names (char const *name1, char const *name2)
{
  if (locale_specific_sorting)
    {
      int r;
      errno = 0;
      if (ignore_file_name_case)
	r = strcasecoll (name1, name2);
      else
	r = strcoll (name1, name2);
      if (errno)
	{
	  error (0, errno, _("cannot compare file names `%s' and `%s'"),
		 name1, name2);
	  longjmp (failed_locale_specific_sorting, 1);
	}
      return r;
    }

  return (ignore_file_name_case
	  ? strcasecmp (name1, name2)
	  : file_name_cmp (name1, name2));
}