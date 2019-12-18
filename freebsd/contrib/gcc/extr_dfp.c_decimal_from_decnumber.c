#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decimal128 ;
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_8__ {int status; scalar_t__ traps; } ;
typedef  TYPE_1__ decContext ;
struct TYPE_9__ {scalar_t__ cl; int sign; int decimal; scalar_t__ sig; } ;
typedef  TYPE_2__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_INIT_DECIMAL128 ; 
 int DEC_Overflow ; 
 int /*<<< orphan*/  decContextDefault (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ decNumberIsInfinite (int /*<<< orphan*/ *) ; 
 scalar_t__ decNumberIsNaN (int /*<<< orphan*/ *) ; 
 scalar_t__ decNumberIsNegative (int /*<<< orphan*/ *) ; 
 scalar_t__ decNumberIsZero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decimal128FromNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* rvc_inf ; 
 scalar_t__ rvc_nan ; 
 scalar_t__ rvc_normal ; 
 scalar_t__ rvc_zero ; 

__attribute__((used)) static void
decimal_from_decnumber (REAL_VALUE_TYPE *r, decNumber *dn, decContext *context)
{
  memset (r, 0, sizeof (REAL_VALUE_TYPE));

  r->cl = rvc_normal;
  if (decNumberIsZero (dn))
    r->cl = rvc_zero;
  if (decNumberIsNaN (dn))
    r->cl = rvc_nan;
  if (decNumberIsInfinite (dn))
    r->cl = rvc_inf;
  if (context->status & DEC_Overflow)
    r->cl = rvc_inf;
  if (decNumberIsNegative (dn))
    r->sign = 1;
  r->decimal = 1;

  if (r->cl != rvc_normal)
    return;

  decContextDefault (context, DEC_INIT_DECIMAL128);
  context->traps = 0;

  decimal128FromNumber ((decimal128 *) r->sig, dn, context);
}