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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct type* ada_to_fixed_type (struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct value* value_from_contents_and_address (struct type*,char*,int /*<<< orphan*/ ) ; 

struct value *
ada_to_fixed_value (struct type *type0, char *valaddr, CORE_ADDR address,
		    struct value *val0)
{
  struct type *type = ada_to_fixed_type (type0, valaddr, address, NULL);
  if (type == type0 && val0 != NULL)
    return val0;
  else
    return value_from_contents_and_address (type, valaddr, address);
}