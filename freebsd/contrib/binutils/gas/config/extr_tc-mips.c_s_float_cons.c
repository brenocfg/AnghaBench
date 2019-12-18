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
struct insn_label_list {int /*<<< orphan*/ * label; } ;
struct TYPE_3__ {struct insn_label_list* label_list; } ;
typedef  TYPE_1__ segment_info_type ;

/* Variables and functions */
 scalar_t__ auto_align ; 
 int /*<<< orphan*/  float_cons (int) ; 
 int /*<<< orphan*/  mips_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_clear_insn_labels () ; 
 int /*<<< orphan*/  mips_emit_delays () ; 
 int /*<<< orphan*/  now_seg ; 
 TYPE_1__* seg_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s_float_cons (int type)
{
  segment_info_type *si = seg_info (now_seg);
  struct insn_label_list *l = si->label_list;
  symbolS *label;

  label = l != NULL ? l->label : NULL;

  mips_emit_delays ();

  if (auto_align)
    {
      if (type == 'd')
	mips_align (3, 0, label);
      else
	mips_align (2, 0, label);
    }

  mips_clear_insn_labels ();

  float_cons (type);
}