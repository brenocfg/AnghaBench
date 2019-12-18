#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWARF2_DEBUG_INFO ; 
 int /*<<< orphan*/  GNU_LINKONCE_INFO ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static asection *
find_debug_info (bfd *abfd, asection *after_sec)
{
  asection * msec;

  msec = after_sec != NULL ? after_sec->next : abfd->sections;

  while (msec)
    {
      if (strcmp (msec->name, DWARF2_DEBUG_INFO) == 0)
	return msec;

      if (CONST_STRNEQ (msec->name, GNU_LINKONCE_INFO))
	return msec;

      msec = msec->next;
    }

  return NULL;
}