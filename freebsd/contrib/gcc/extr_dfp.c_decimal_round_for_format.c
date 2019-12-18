#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct real_format {int dummy; } ;
typedef  int /*<<< orphan*/  decimal64 ;
typedef  int /*<<< orphan*/  decimal32 ;
typedef  int /*<<< orphan*/  decimal128 ;
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_9__ {scalar_t__ traps; } ;
typedef  TYPE_1__ decContext ;
struct TYPE_10__ {scalar_t__ cl; scalar_t__ sig; } ;
typedef  TYPE_2__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_INIT_DECIMAL128 ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL32 ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL64 ; 
 int /*<<< orphan*/  decContextDefault (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decimal128ToNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decimal32FromNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decimal32ToNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decimal64FromNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decimal64ToNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct real_format const decimal_double_format ; 
 int /*<<< orphan*/  decimal_from_decnumber (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct real_format const decimal_quad_format ; 
 struct real_format const decimal_single_format ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ rvc_normal ; 

void
decimal_round_for_format (const struct real_format *fmt, REAL_VALUE_TYPE *r)
{
  decNumber dn;
  decContext set;

  /* Real encoding occurs later.  */
  if (r->cl != rvc_normal)
    return;

  decContextDefault (&set, DEC_INIT_DECIMAL128);
  set.traps = 0;
  decimal128ToNumber ((decimal128 *) r->sig, &dn);

  if (fmt == &decimal_quad_format)
    {
      /* The internal format is already in this format.  */
      return;
    }
  else if (fmt == &decimal_single_format)
    {
      decimal32 d32;
      decContextDefault (&set, DEC_INIT_DECIMAL32);
      set.traps = 0;

      decimal32FromNumber (&d32, &dn, &set);
      decimal32ToNumber (&d32, &dn);
    }
  else if (fmt == &decimal_double_format)
    {
      decimal64 d64;
      decContextDefault (&set, DEC_INIT_DECIMAL64);
      set.traps = 0;

      decimal64FromNumber (&d64, &dn, &set);
      decimal64ToNumber (&d64, &dn);
    }
  else
    gcc_unreachable ();

  decimal_from_decnumber (r, &dn, &set);
}