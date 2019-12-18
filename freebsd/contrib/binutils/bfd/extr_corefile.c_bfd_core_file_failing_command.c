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
struct TYPE_5__ {scalar_t__ format; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 char const* BFD_SEND (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _core_file_failing_command ; 
 scalar_t__ bfd_core ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

const char *
bfd_core_file_failing_command (bfd *abfd)
{
  if (abfd->format != bfd_core)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }
  return BFD_SEND (abfd, _core_file_failing_command, (abfd));
}