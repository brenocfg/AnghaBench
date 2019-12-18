#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {scalar_t__ format; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_SEND (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _core_file_matches_executable_p ; 
 scalar_t__ bfd_core ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

bfd_boolean
core_file_matches_executable_p (bfd *core_bfd, bfd *exec_bfd)
{
  if (core_bfd->format != bfd_core || exec_bfd->format != bfd_object)
    {
      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }

  return BFD_SEND (core_bfd, _core_file_matches_executable_p,
		   (core_bfd, exec_bfd));
}