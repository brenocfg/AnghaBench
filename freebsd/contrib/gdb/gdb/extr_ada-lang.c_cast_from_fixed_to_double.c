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
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  ada_fixed_to_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_double ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 struct value* value_from_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
cast_from_fixed_to_double (struct value *arg)
{
  DOUBLEST val = ada_fixed_to_float (VALUE_TYPE (arg),
				     value_as_long (arg));
  return value_from_double (builtin_type_double, val);
}