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
struct value {int dummy; } ;

/* Variables and functions */
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* ada_to_fixed_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct value*) ; 
 struct value* unwrap_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_ind (struct value*) ; 

struct value *
ada_value_ind (struct value *val0)
{
  struct value *val = unwrap_value (value_ind (val0));
  return ada_to_fixed_value (VALUE_TYPE (val), 0,
			     VALUE_ADDRESS (val) + VALUE_OFFSET (val), val);
}