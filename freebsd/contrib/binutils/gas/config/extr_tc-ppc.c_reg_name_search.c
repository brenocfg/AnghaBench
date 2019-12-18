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
struct pd_reg {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reg_name_search (const struct pd_reg *regs, int regcount, const char *name)
{
  int middle, low, high;
  int cmp;

  low = 0;
  high = regcount - 1;

  do
    {
      middle = (low + high) / 2;
      cmp = strcasecmp (name, regs[middle].name);
      if (cmp < 0)
	high = middle - 1;
      else if (cmp > 0)
	low = middle + 1;
      else
	return regs[middle].value;
    }
  while (low <= high);

  return -1;
}