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
struct itbl_range {scalar_t__ sbit; scalar_t__ ebit; } ;
struct itbl_entry {scalar_t__ processor; unsigned long value; struct itbl_range range; struct itbl_entry* next; } ;
typedef  int /*<<< orphan*/  e_type ;
typedef  scalar_t__ e_processor ;

/* Variables and functions */
 unsigned long apply_range (unsigned long,struct itbl_range) ; 
 struct itbl_entry** get_entries (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct itbl_entry *
find_entry_byval (e_processor processor, e_type type,
		  unsigned long val, struct itbl_range *r)
{
  struct itbl_entry *e, **es;
  unsigned long eval;

  es = get_entries (processor, type);
  for (e = *es; e; e = e->next)	/* for each entry, ...  */
    {
      if (processor != e->processor)
	continue;
      /* For insns, we might not know the range of the opcode,
	 * so a range of 0 will allow this routine to match against
	 * the range of the entry to be compared with.
	 * This could cause ambiguities.
	 * For operands, we get an extracted value and a range.
	 */
      /* if range is 0, mask val against the range of the compared entry.  */
      if (r == 0)		/* if no range passed, must be whole 32-bits
			 * so create 32-bit value from entry's range */
	{
	  eval = apply_range (e->value, e->range);
	  val &= apply_range (0xffffffff, e->range);
	}
      else if ((r->sbit == e->range.sbit && r->ebit == e->range.ebit)
	       || (e->range.sbit == 0 && e->range.ebit == 0))
	{
	  eval = apply_range (e->value, *r);
	  val = apply_range (val, *r);
	}
      else
	continue;
      if (val == eval)
	return e;
    }
  return 0;
}