#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* fip; } ;
typedef  TYPE_1__ hash_table_entry ;
struct TYPE_6__ {TYPE_3__* defs_decs; } ;
typedef  TYPE_2__ file_info ;
struct TYPE_7__ {struct TYPE_7__* next_in_file; } ;
typedef  TYPE_3__ def_dec_info ;

/* Variables and functions */

__attribute__((used)) static void
reverse_def_dec_list (const hash_table_entry *hp)
{
  file_info *file_p = hp->fip;
  def_dec_info *prev = NULL;
  def_dec_info *current = (def_dec_info *) file_p->defs_decs;

  if (!current)
    return;        		/* no list to reverse */

  prev = current;
  if (! (current = (def_dec_info *) current->next_in_file))
    return;        		/* can't reverse a single list element */

  prev->next_in_file = NULL;

  while (current)
    {
      def_dec_info *next = (def_dec_info *) current->next_in_file;

      current->next_in_file = prev;
      prev = current;
      current = next;
    }

  file_p->defs_decs = prev;
}