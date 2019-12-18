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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_NFIELDS (struct type*) ; 
 int ada_is_variant_part (struct type*,scalar_t__) ; 

__attribute__((used)) static int
contains_variant_part (struct type *type)
{
  int f;

  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT
      || TYPE_NFIELDS (type) <= 0)
    return 0;
  return ada_is_variant_part (type, TYPE_NFIELDS (type) - 1);
}