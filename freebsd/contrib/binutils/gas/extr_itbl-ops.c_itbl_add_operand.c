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
struct itbl_field {struct itbl_field* next; } ;
struct itbl_entry {struct itbl_field* fields; } ;

/* Variables and functions */
 struct itbl_field* alloc_field (int /*<<< orphan*/ ,int,int,unsigned long) ; 
 int /*<<< orphan*/  get_type (int) ; 

struct itbl_field *
itbl_add_operand (struct itbl_entry *e, int yytype, int sbit,
		  int ebit, unsigned long flags)
{
  struct itbl_field *f, **last_f;
  if (!e)
    return 0;
  /* Add to end of fields' list.  */
  f = alloc_field (get_type (yytype), sbit, ebit, flags);
  if (f)
    {
      last_f = &e->fields;
      while (*last_f)
	last_f = &(*last_f)->next;
      *last_f = f;
      f->next = 0;
    }
  return f;
}