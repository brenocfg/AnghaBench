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
struct df_insn_info {int dummy; } ;
struct df {unsigned int insns_size; int /*<<< orphan*/  insns; } ;

/* Variables and functions */
 int get_max_uid () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void 
df_grow_insn_info (struct df *df)
{
  unsigned int new_size = get_max_uid () + 1;
  if (df->insns_size < new_size)
    {
      new_size += new_size / 4;
      df->insns = xrealloc (df->insns, 
			    new_size *sizeof (struct df_insn_info *));
      memset (df->insns + df->insns_size, 0,
	      (new_size - df->insns_size) *sizeof (struct df_insn_info *));
      df->insns_size = new_size;
    }
}