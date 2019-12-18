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
struct operand_data {char* predicate; char* constraint; scalar_t__ mode; scalar_t__ strict_low; scalar_t__ eliminable; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
compare_operands (struct operand_data *d0, struct operand_data *d1)
{
  const char *p0, *p1;

  p0 = d0->predicate;
  if (!p0)
    p0 = "";
  p1 = d1->predicate;
  if (!p1)
    p1 = "";
  if (strcmp (p0, p1) != 0)
    return 0;

  p0 = d0->constraint;
  if (!p0)
    p0 = "";
  p1 = d1->constraint;
  if (!p1)
    p1 = "";
  if (strcmp (p0, p1) != 0)
    return 0;

  if (d0->mode != d1->mode)
    return 0;

  if (d0->strict_low != d1->strict_low)
    return 0;

  if (d0->eliminable != d1->eliminable)
    return 0;

  return 1;
}