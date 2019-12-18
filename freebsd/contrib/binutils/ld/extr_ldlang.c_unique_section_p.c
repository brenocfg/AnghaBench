#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct unique_sections {int /*<<< orphan*/  name; struct unique_sections* next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {char* name; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {scalar_t__ relocatable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_is_group_section (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_3__ link_info ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct unique_sections* unique_section_list ; 
 scalar_t__ wildcardp (int /*<<< orphan*/ ) ; 

bfd_boolean
unique_section_p (const asection *sec)
{
  struct unique_sections *unam;
  const char *secnam;

  if (link_info.relocatable
      && sec->owner != NULL
      && bfd_is_group_section (sec->owner, sec))
    return TRUE;

  secnam = sec->name;
  for (unam = unique_section_list; unam; unam = unam->next)
    if (wildcardp (unam->name)
	? fnmatch (unam->name, secnam, 0) == 0
	: strcmp (unam->name, secnam) == 0)
      {
	return TRUE;
      }

  return FALSE;
}