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
typedef  int /*<<< orphan*/  lin ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
compare_line_list (char * const list1[], size_t const lengths1[],
		   char * const list2[], size_t const lengths2[],
		   lin nl)
{
  char * const *l1 = list1;
  char * const *l2 = list2;
  size_t const *lgths1 = lengths1;
  size_t const *lgths2 = lengths2;

  while (nl--)
    if (!*l1 || !*l2 || *lgths1 != *lgths2++
	|| memcmp (*l1++, *l2++, *lgths1++) != 0)
      return false;
  return true;
}