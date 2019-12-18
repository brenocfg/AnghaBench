#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 unsigned int COMPLAIN ; 
 unsigned int PRETEND ; 
 int SEC_DEBUGGING ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

unsigned int
_bfd_elf_default_action_discarded (asection *sec)
{
  if (sec->flags & SEC_DEBUGGING)
    return PRETEND;

  if (strcmp (".eh_frame", sec->name) == 0)
    return 0;

  if (strcmp (".gcc_except_table", sec->name) == 0)
    return 0;

  return COMPLAIN | PRETEND;
}