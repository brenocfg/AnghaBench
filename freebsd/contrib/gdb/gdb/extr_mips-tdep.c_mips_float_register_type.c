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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 struct type* builtin_type_ieee_single_big ; 
 struct type* builtin_type_ieee_single_little ; 

__attribute__((used)) static struct type *
mips_float_register_type (void)
{
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    return builtin_type_ieee_single_big;
  else
    return builtin_type_ieee_single_little;
}