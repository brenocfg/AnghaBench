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
typedef  int /*<<< orphan*/  symbolS ;
struct insn_label_list {struct insn_label_list* next; int /*<<< orphan*/ * label; } ;
struct TYPE_3__ {struct insn_label_list* label_list; } ;
typedef  TYPE_1__ segment_info_type ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_emit_label (int /*<<< orphan*/ *) ; 
 struct insn_label_list* free_insn_labels ; 
 int /*<<< orphan*/  now_seg ; 
 TYPE_1__* seg_info (int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

void
mips_define_label (symbolS *sym)
{
  segment_info_type *si = seg_info (now_seg);
  struct insn_label_list *l;

  if (free_insn_labels == NULL)
    l = (struct insn_label_list *) xmalloc (sizeof *l);
  else
    {
      l = free_insn_labels;
      free_insn_labels = l->next;
    }

  l->label = sym;
  l->next = si->label_list;
  si->label_list = l;

#ifdef OBJ_ELF
  dwarf2_emit_label (sym);
#endif
}