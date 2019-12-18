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
struct floatformat {int dummy; } ;
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  floatformat_arm_ext_big ; 
 int /*<<< orphan*/  floatformat_arm_ext_littlebyte_bigword ; 
 int /*<<< orphan*/  floatformat_from_doublest (struct floatformat const*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  floatformat_to_doublest (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
convert_from_extended (const struct floatformat *fmt, const void *ptr,
		       void *dbl)
{
  DOUBLEST d;
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    floatformat_to_doublest (&floatformat_arm_ext_big, ptr, &d);
  else
    floatformat_to_doublest (&floatformat_arm_ext_littlebyte_bigword,
			     ptr, &d);
  floatformat_from_doublest (fmt, &d, dbl);
}