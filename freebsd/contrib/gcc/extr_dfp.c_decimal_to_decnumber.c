#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decimal128 ;
struct TYPE_12__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_13__ {scalar_t__ traps; } ;
typedef  TYPE_2__ decContext ;
struct TYPE_14__ {int cl; scalar_t__ sign; scalar_t__ sig; int /*<<< orphan*/  decimal; int /*<<< orphan*/  signalling; } ;
typedef  TYPE_3__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL128 ; 
 int /*<<< orphan*/  decContextDefault (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberFromString (TYPE_1__*,char*,TYPE_2__*) ; 
 scalar_t__ decNumberIsNegative (TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decimal128ToNumber (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

__attribute__((used)) static void
decimal_to_decnumber (const REAL_VALUE_TYPE *r, decNumber *dn)
{
  decContext set;
  decContextDefault (&set, DEC_INIT_DECIMAL128);
  set.traps = 0;

  switch (r->cl)
    {
    case rvc_zero:
      decNumberZero (dn);
      break;
    case rvc_inf:
      decNumberFromString (dn, (char *)"Infinity", &set);
      break;
    case rvc_nan:
      if (r->signalling)
        decNumberFromString (dn, (char *)"snan", &set);
      else
        decNumberFromString (dn, (char *)"nan", &set);
      break;
    case rvc_normal:
      gcc_assert (r->decimal);
      decimal128ToNumber ((decimal128 *) r->sig, dn);
      break;
    default:
      gcc_unreachable ();
    }

  /* Fix up sign bit.  */
  if (r->sign != decNumberIsNegative (dn))
    dn->bits ^= DECNEG;
}