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
struct dump_list_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  type; struct dump_list_entry* next; } ;
struct TYPE_2__ {unsigned int e_shnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECTION_NAME (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct dump_list_entry* dump_sects_byname ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  request_dump (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ section_headers ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initialise_dumps_byname (void)
{
  struct dump_list_entry *cur;

  for (cur = dump_sects_byname; cur; cur = cur->next)
    {
      unsigned int i;
      int any;

      for (i = 0, any = 0; i < elf_header.e_shnum; i++)
	if (streq (SECTION_NAME (section_headers + i), cur->name))
	  {
	    request_dump (i, cur->type);
	    any = 1;
	  }

      if (!any)
	warn (_("Section '%s' was not dumped because it does not exist!\n"),
	      cur->name);
    }
}