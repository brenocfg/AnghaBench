#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ direction; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 TYPE_1__* BFD_SEND (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ bfd_archive ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_format (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openr_next_archived_file ; 
 scalar_t__ write_direction ; 

bfd *
bfd_openr_next_archived_file (bfd *archive, bfd *last_file)
{
  if ((bfd_get_format (archive) != bfd_archive) ||
      (archive->direction == write_direction))
    {
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }

  return BFD_SEND (archive,
		   openr_next_archived_file, (archive, last_file));
}