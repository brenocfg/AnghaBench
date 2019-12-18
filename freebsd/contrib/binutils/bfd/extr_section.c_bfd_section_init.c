#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  section_count; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_11__ {int id; TYPE_1__* owner; int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_SEND (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _new_section_hook ; 
 int /*<<< orphan*/  bfd_section_list_append (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static asection *
bfd_section_init (bfd *abfd, asection *newsect)
{
  static int section_id = 0x10;  /* id 0 to 3 used by STD_SECTION.  */

  newsect->id = section_id;
  newsect->index = abfd->section_count;
  newsect->owner = abfd;

  if (! BFD_SEND (abfd, _new_section_hook, (abfd, newsect)))
    return NULL;

  section_id++;
  abfd->section_count++;
  bfd_section_list_append (abfd, newsect);
  return newsect;
}