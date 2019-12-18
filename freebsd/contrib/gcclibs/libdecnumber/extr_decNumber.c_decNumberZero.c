#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int digits; scalar_t__* lsu; scalar_t__ exponent; scalar_t__ bits; } ;
typedef  TYPE_1__ decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

decNumber *
decNumberZero (decNumber * dn)
{

#if DECCHECK
  if (decCheckOperands (dn, DECUNUSED, DECUNUSED, DECUNUSED))
    return dn;
#endif

  dn->bits = 0;
  dn->exponent = 0;
  dn->digits = 1;
  dn->lsu[0] = 0;
  return dn;
}