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
struct TYPE_2__ {int insn; } ;

/* Variables and functions */
 unsigned int NUM_MAPPINGS ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* subtype_mappings ; 

__attribute__((used)) static int
insn_to_subtype (int insn)
{
  unsigned int i;
  for (i=0; i<NUM_MAPPINGS; i++)
    if (insn == subtype_mappings[i].insn)
      return i;
  abort ();
}