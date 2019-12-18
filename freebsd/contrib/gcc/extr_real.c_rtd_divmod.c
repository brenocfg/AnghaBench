#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned long* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int REAL_EXP (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGSZ ; 
 unsigned long SIG_MSB ; 
 scalar_t__ cmp_significands (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lshift_significand_1 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  sub_significands (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
rtd_divmod (REAL_VALUE_TYPE *num, REAL_VALUE_TYPE *den)
{
  unsigned long q, msb;
  int expn = REAL_EXP (num), expd = REAL_EXP (den);

  if (expn < expd)
    return 0;

  q = msb = 0;
  goto start;
  do
    {
      msb = num->sig[SIGSZ-1] & SIG_MSB;
      q <<= 1;
      lshift_significand_1 (num, num);
    start:
      if (msb || cmp_significands (num, den) >= 0)
	{
	  sub_significands (num, num, den, 0);
	  q |= 1;
	}
    }
  while (--expn >= expd);

  SET_REAL_EXP (num, expd);
  normalize (num);

  return q;
}