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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {unsigned long extended_names_size; char* extended_names; } ;

/* Variables and functions */
 TYPE_1__* bfd_ardata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_malformed_archive ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 unsigned long strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
get_extended_arelt_filename (bfd *arch, const char *name)
{
  unsigned long index = 0;

  /* Should extract string so that I can guarantee not to overflow into
     the next region, but I'm too lazy.  */
  errno = 0;
  /* Skip first char, which is '/' in SVR4 or ' ' in some other variants.  */
  index = strtol (name + 1, NULL, 10);
  if (errno != 0 || index >= bfd_ardata (arch)->extended_names_size)
    {
      bfd_set_error (bfd_error_malformed_archive);
      return NULL;
    }

  return bfd_ardata (arch)->extended_names + index;
}