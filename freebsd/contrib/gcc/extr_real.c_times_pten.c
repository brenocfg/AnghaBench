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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  do_divide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_multiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * real_digit (int) ; 
 int /*<<< orphan*/  ten_to_ptwo (int) ; 

__attribute__((used)) static void
times_pten (REAL_VALUE_TYPE *r, int exp)
{
  REAL_VALUE_TYPE pten, *rr;
  bool negative = (exp < 0);
  int i;

  if (negative)
    {
      exp = -exp;
      pten = *real_digit (1);
      rr = &pten;
    }
  else
    rr = r;

  for (i = 0; exp > 0; ++i, exp >>= 1)
    if (exp & 1)
      do_multiply (rr, rr, ten_to_ptwo (i));

  if (negative)
    do_divide (r, r, &pten);
}