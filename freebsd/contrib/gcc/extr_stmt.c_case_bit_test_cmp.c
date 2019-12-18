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
struct case_bit_test {scalar_t__ bits; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
case_bit_test_cmp (const void *p1, const void *p2)
{
  const struct case_bit_test *d1 = p1;
  const struct case_bit_test *d2 = p2;

  if (d2->bits != d1->bits)
    return d2->bits - d1->bits;

  /* Stabilize the sort.  */
  return CODE_LABEL_NUMBER (d2->label) - CODE_LABEL_NUMBER (d1->label);
}