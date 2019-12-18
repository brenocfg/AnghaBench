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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  desc_data_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thin_descriptor_type (struct type*) ; 
 struct value* value_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_copy (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct value *
thin_data_pntr (struct value *val)
{
  struct type *type = VALUE_TYPE (val);
  if (TYPE_CODE (type) == TYPE_CODE_PTR)
    return value_cast (desc_data_type (thin_descriptor_type (type)),
		       value_copy (val));
  else
    return value_from_longest (desc_data_type (thin_descriptor_type (type)),
			       VALUE_ADDRESS (val) + VALUE_OFFSET (val));
}