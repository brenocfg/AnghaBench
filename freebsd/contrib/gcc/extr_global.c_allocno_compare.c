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
struct TYPE_2__ {int freq; double live_length; double size; int /*<<< orphan*/  n_refs; } ;

/* Variables and functions */
 int REG_FREQ_MAX ; 
 TYPE_1__* allocno ; 
 int floor_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
allocno_compare (const void *v1p, const void *v2p)
{
  int v1 = *(const int *)v1p, v2 = *(const int *)v2p;
  /* Note that the quotient will never be bigger than
     the value of floor_log2 times the maximum number of
     times a register can occur in one insn (surely less than 100)
     weighted by the frequency (maximally REG_FREQ_MAX).
     Multiplying this by 10000/REG_FREQ_MAX can't overflow.  */
  int pri1
    = (((double) (floor_log2 (allocno[v1].n_refs) * allocno[v1].freq)
	/ allocno[v1].live_length)
       * (10000 / REG_FREQ_MAX) * allocno[v1].size);
  int pri2
    = (((double) (floor_log2 (allocno[v2].n_refs) * allocno[v2].freq)
	/ allocno[v2].live_length)
       * (10000 / REG_FREQ_MAX) * allocno[v2].size);
  if (pri2 - pri1)
    return pri2 - pri1;

  /* If regs are equally good, sort by allocno,
     so that the results of qsort leave nothing to chance.  */
  return v1 - v2;
}