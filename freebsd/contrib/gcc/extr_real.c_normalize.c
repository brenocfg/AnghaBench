#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned long* sig; int /*<<< orphan*/  sign; int /*<<< orphan*/  cl; scalar_t__ decimal; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int MAX_EXP ; 
 int REAL_EXP (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGSZ ; 
 int /*<<< orphan*/  get_inf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_zero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lshift_significand (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rvc_zero ; 

__attribute__((used)) static void
normalize (REAL_VALUE_TYPE *r)
{
  int shift = 0, exp;
  int i, j;

  if (r->decimal)
    return;

  /* Find the first word that is nonzero.  */
  for (i = SIGSZ - 1; i >= 0; i--)
    if (r->sig[i] == 0)
      shift += HOST_BITS_PER_LONG;
    else
      break;

  /* Zero significand flushes to zero.  */
  if (i < 0)
    {
      r->cl = rvc_zero;
      SET_REAL_EXP (r, 0);
      return;
    }

  /* Find the first bit that is nonzero.  */
  for (j = 0; ; j++)
    if (r->sig[i] & ((unsigned long)1 << (HOST_BITS_PER_LONG - 1 - j)))
      break;
  shift += j;

  if (shift > 0)
    {
      exp = REAL_EXP (r) - shift;
      if (exp > MAX_EXP)
	get_inf (r, r->sign);
      else if (exp < -MAX_EXP)
	get_zero (r, r->sign);
      else
	{
	  SET_REAL_EXP (r, exp);
	  lshift_significand (r, r, shift);
	}
    }
}