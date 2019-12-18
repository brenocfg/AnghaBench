#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_error_type ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_TRADITIONAL_FORMAT ; 
 int /*<<< orphan*/  TARGET_ARCH ; 
 int /*<<< orphan*/  TARGET_FORMAT ; 
 int /*<<< orphan*/  TARGET_MACH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bfd_errmsg (scalar_t__) ; 
 scalar_t__ bfd_error_invalid_target ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_1__* bfd_openw (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_traditional_format ; 
 TYPE_1__* stdoutput ; 

void
output_file_create (char *name)
{
  if (name[0] == '-' && name[1] == '\0')
    as_fatal (_("can't open a bfd on stdout %s"), name);

  else if (!(stdoutput = bfd_openw (name, TARGET_FORMAT)))
    {
      bfd_error_type err = bfd_get_error ();

      if (err == bfd_error_invalid_target)
	as_fatal (_("selected target format '%s' unknown"), TARGET_FORMAT);
      else
	as_fatal (_("can't create %s: %s"), name, bfd_errmsg (err));
    }

  bfd_set_format (stdoutput, bfd_object);
  bfd_set_arch_mach (stdoutput, TARGET_ARCH, TARGET_MACH);
  if (flag_traditional_format)
    stdoutput->flags |= BFD_TRADITIONAL_FORMAT;
}