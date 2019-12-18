#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_4__ {int is_directive; unsigned int directive_index; } ;
typedef  TYPE_1__ cpp_hashnode ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ N_DIRECTIVES ; 
 TYPE_1__* cpp_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dtable ; 

void
_cpp_init_directives (cpp_reader *pfile)
{
  unsigned int i;
  cpp_hashnode *node;

  for (i = 0; i < (unsigned int) N_DIRECTIVES; i++)
    {
      node = cpp_lookup (pfile, dtable[i].name, dtable[i].length);
      node->is_directive = 1;
      node->directive_index = i;
    }
}