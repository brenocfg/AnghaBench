#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct real_format {int b; int emax; int log2_b; int p; int pnan; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {int sign; struct TYPE_8__* sig; int /*<<< orphan*/  cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGNIFICAND_BITS ; 
 int SIGSZ ; 
 int /*<<< orphan*/  clear_significand_below (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clear_significand_bit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decimal_real_maxval (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gcc_assert (struct real_format const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  rvc_normal ; 

void
real_maxval (REAL_VALUE_TYPE *r, int sign, enum machine_mode mode)
{
  const struct real_format *fmt;
  int np2;

  fmt = REAL_MODE_FORMAT (mode);
  gcc_assert (fmt);
  memset (r, 0, sizeof (*r));
  
  if (fmt->b == 10)
    decimal_real_maxval (r, sign, mode);
  else
    {
      r->cl = rvc_normal;
      r->sign = sign;
      SET_REAL_EXP (r, fmt->emax * fmt->log2_b);

      np2 = SIGNIFICAND_BITS - fmt->p * fmt->log2_b;
      memset (r->sig, -1, SIGSZ * sizeof (unsigned long));
      clear_significand_below (r, np2);

      if (fmt->pnan < fmt->p)
	/* This is an IBM extended double format made up of two IEEE
	   doubles.  The value of the long double is the sum of the
	   values of the two parts.  The most significant part is
	   required to be the value of the long double rounded to the
	   nearest double.  Rounding means we need a slightly smaller
	   value for LDBL_MAX.  */
        clear_significand_bit (r, SIGNIFICAND_BITS - fmt->pnan);
    }
}