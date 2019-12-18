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
typedef  scalar_t__ subsegT ;
struct line_subseg {scalar_t__ subseg; int /*<<< orphan*/ * head; int /*<<< orphan*/ ** ptail; struct line_subseg* next; } ;
struct line_seg {scalar_t__ seg; struct line_subseg* head; struct line_seg* next; } ;
typedef  scalar_t__ segT ;

/* Variables and functions */
 struct line_seg* all_segs ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct line_subseg *
get_line_subseg (segT seg, subsegT subseg)
{
  static segT last_seg;
  static subsegT last_subseg;
  static struct line_subseg *last_line_subseg;

  struct line_seg **ps, *s;
  struct line_subseg **pss, *ss;

  if (seg == last_seg && subseg == last_subseg)
    return last_line_subseg;

  for (ps = &all_segs; (s = *ps) != NULL; ps = &s->next)
    if (s->seg == seg)
      goto found_seg;

  s = (struct line_seg *) xmalloc (sizeof (*s));
  s->next = NULL;
  s->seg = seg;
  s->head = NULL;
  *ps = s;

 found_seg:
  for (pss = &s->head; (ss = *pss) != NULL ; pss = &ss->next)
    {
      if (ss->subseg == subseg)
	goto found_subseg;
      if (ss->subseg > subseg)
	break;
    }

  ss = (struct line_subseg *) xmalloc (sizeof (*ss));
  ss->next = *pss;
  ss->subseg = subseg;
  ss->head = NULL;
  ss->ptail = &ss->head;
  *pss = ss;

 found_subseg:
  last_seg = seg;
  last_subseg = subseg;
  last_line_subseg = ss;

  return ss;
}