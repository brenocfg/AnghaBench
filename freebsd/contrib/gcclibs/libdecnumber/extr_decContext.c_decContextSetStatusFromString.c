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
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_Clamped ; 
 int /*<<< orphan*/  DEC_Condition_CS ; 
 int /*<<< orphan*/  DEC_Condition_DI ; 
 int /*<<< orphan*/  DEC_Condition_DU ; 
 int /*<<< orphan*/  DEC_Condition_DZ ; 
 int /*<<< orphan*/  DEC_Condition_IC ; 
 int /*<<< orphan*/  DEC_Condition_IE ; 
 int /*<<< orphan*/  DEC_Condition_IO ; 
 int /*<<< orphan*/  DEC_Condition_IS ; 
 int /*<<< orphan*/  DEC_Condition_LD ; 
 int /*<<< orphan*/  DEC_Condition_OV ; 
 int /*<<< orphan*/  DEC_Condition_PA ; 
 int /*<<< orphan*/  DEC_Condition_RO ; 
 int /*<<< orphan*/  DEC_Condition_SU ; 
 int /*<<< orphan*/  DEC_Condition_UN ; 
 int /*<<< orphan*/  DEC_Condition_ZE ; 
 int /*<<< orphan*/  DEC_Conversion_syntax ; 
 int /*<<< orphan*/  DEC_Division_by_zero ; 
 int /*<<< orphan*/  DEC_Division_impossible ; 
 int /*<<< orphan*/  DEC_Division_undefined ; 
 int /*<<< orphan*/  DEC_Inexact ; 
 int /*<<< orphan*/  DEC_Insufficient_storage ; 
 int /*<<< orphan*/  DEC_Invalid_context ; 
 int /*<<< orphan*/  DEC_Invalid_operation ; 
 int /*<<< orphan*/  DEC_Lost_digits ; 
 int /*<<< orphan*/  DEC_Overflow ; 
 int /*<<< orphan*/  DEC_Rounded ; 
 int /*<<< orphan*/  DEC_Subnormal ; 
 int /*<<< orphan*/  DEC_Underflow ; 
 int /*<<< orphan*/ * decContextSetStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

decContext *
decContextSetStatusFromString (decContext * context, const char *string)
{
  if (strcmp (string, DEC_Condition_CS) == 0)
    return decContextSetStatus (context, DEC_Conversion_syntax);
  if (strcmp (string, DEC_Condition_DZ) == 0)
    return decContextSetStatus (context, DEC_Division_by_zero);
  if (strcmp (string, DEC_Condition_DI) == 0)
    return decContextSetStatus (context, DEC_Division_impossible);
  if (strcmp (string, DEC_Condition_DU) == 0)
    return decContextSetStatus (context, DEC_Division_undefined);
  if (strcmp (string, DEC_Condition_IE) == 0)
    return decContextSetStatus (context, DEC_Inexact);
  if (strcmp (string, DEC_Condition_IS) == 0)
    return decContextSetStatus (context, DEC_Insufficient_storage);
  if (strcmp (string, DEC_Condition_IC) == 0)
    return decContextSetStatus (context, DEC_Invalid_context);
  if (strcmp (string, DEC_Condition_IO) == 0)
    return decContextSetStatus (context, DEC_Invalid_operation);
#if DECSUBSET
  if (strcmp (string, DEC_Condition_LD) == 0)
    return decContextSetStatus (context, DEC_Lost_digits);
#endif
  if (strcmp (string, DEC_Condition_OV) == 0)
    return decContextSetStatus (context, DEC_Overflow);
  if (strcmp (string, DEC_Condition_PA) == 0)
    return decContextSetStatus (context, DEC_Clamped);
  if (strcmp (string, DEC_Condition_RO) == 0)
    return decContextSetStatus (context, DEC_Rounded);
  if (strcmp (string, DEC_Condition_SU) == 0)
    return decContextSetStatus (context, DEC_Subnormal);
  if (strcmp (string, DEC_Condition_UN) == 0)
    return decContextSetStatus (context, DEC_Underflow);
  if (strcmp (string, DEC_Condition_ZE) == 0)
    return context;
  return NULL;			/* Multiple status, or unknown */
}