#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DECNAN ; 
 int DEC_NaNs ; 
 int DEC_sNaN ; 
 int /*<<< orphan*/  decContextSetStatus (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 

__attribute__((used)) static void
decStatus (decNumber * dn, uInt status, decContext * set)
{
  if (status & DEC_NaNs)
    {				/* error status -> NaN */
      /* if cause was an sNaN, clear and propagate [NaN is already set up] */
      if (status & DEC_sNaN)
	status &= ~DEC_sNaN;
      else
	{
	  decNumberZero (dn);	/* other error: clean throughout */
	  dn->bits = DECNAN;	/* and make a quiet NaN */
	}
    }
  decContextSetStatus (set, status);
  return;
}