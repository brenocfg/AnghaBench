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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 unsigned int _bfd_elf_default_action_discarded (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ppc_elf_action_discarded (asection *sec)
{
  if (strcmp (".fixup", sec->name) == 0)
    return 0;

  if (strcmp (".got2", sec->name) == 0)
    return 0;

  return _bfd_elf_default_action_discarded (sec);
}