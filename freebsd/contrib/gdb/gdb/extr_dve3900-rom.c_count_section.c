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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_LOAD ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
count_section (bfd *abfd, asection *s, unsigned int *section_count)
{
  if (s->flags & SEC_LOAD && bfd_section_size (abfd, s) != 0)
    (*section_count)++;
}