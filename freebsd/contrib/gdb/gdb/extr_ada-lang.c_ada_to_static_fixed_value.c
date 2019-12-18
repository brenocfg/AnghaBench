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
struct type {int dummy; } ;

/* Variables and functions */
 struct type* VALUE_TYPE (struct value*) ; 
 struct value* coerce_unspec_val_to_type (struct value*,int /*<<< orphan*/ ,struct type*) ; 
 int /*<<< orphan*/  static_unwrap_type (struct type*) ; 
 struct type* to_static_fixed_type (int /*<<< orphan*/ ) ; 

struct value *
ada_to_static_fixed_value (struct value *val)
{
  struct type *type =
    to_static_fixed_type (static_unwrap_type (VALUE_TYPE (val)));
  if (type == VALUE_TYPE (val))
    return val;
  else
    return coerce_unspec_val_to_type (val, 0, type);
}