#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sbit; int ebit; } ;
struct itbl_entry {unsigned long flags; TYPE_1__ range; } ;

/* Variables and functions */
 struct itbl_entry* alloc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  e_insn ; 
 int /*<<< orphan*/  get_processor (int) ; 
 int /*<<< orphan*/  itbl_num_opcodes ; 

struct itbl_entry *
itbl_add_insn (int yyprocessor, char *name, unsigned long value,
	       int sbit, int ebit, unsigned long flags)
{
  struct itbl_entry *e;
  e = alloc_entry (get_processor (yyprocessor), e_insn, name, value);
  if (e)
    {
      e->range.sbit = sbit;
      e->range.ebit = ebit;
      e->flags = flags;
      itbl_num_opcodes++;
    }
  return e;
}