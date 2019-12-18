#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct line_subseg {struct line_entry** ptail; } ;
struct dwarf2_line_info {int dummy; } ;
struct line_entry {struct line_entry* next; struct dwarf2_line_info loc; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 struct line_subseg* get_line_subseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
dwarf2_gen_line_info_1 (symbolS *label, struct dwarf2_line_info *loc)
{
  struct line_subseg *ss;
  struct line_entry *e;

  e = (struct line_entry *) xmalloc (sizeof (*e));
  e->next = NULL;
  e->label = label;
  e->loc = *loc;

  ss = get_line_subseg (now_seg, now_subseg);
  *ss->ptail = e;
  ss->ptail = &e->next;
}