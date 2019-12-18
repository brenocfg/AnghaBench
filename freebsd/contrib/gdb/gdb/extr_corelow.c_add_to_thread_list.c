#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int atoi (scalar_t__) ; 
 scalar_t__ bfd_section_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void
add_to_thread_list (bfd *abfd, asection *asect, void *reg_sect_arg)
{
  int thread_id;
  asection *reg_sect = (asection *) reg_sect_arg;

  if (strncmp (bfd_section_name (abfd, asect), ".reg/", 5) != 0)
    return;

  thread_id = atoi (bfd_section_name (abfd, asect) + 5);

  add_thread (pid_to_ptid (thread_id));

/* Warning, Will Robinson, looking at BFD private data! */

  if (reg_sect != NULL
      && asect->filepos == reg_sect->filepos)	/* Did we find .reg? */
    inferior_ptid = pid_to_ptid (thread_id);	/* Yes, make it current */
}