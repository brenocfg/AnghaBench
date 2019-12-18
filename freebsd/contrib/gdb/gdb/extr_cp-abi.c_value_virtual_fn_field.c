#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
struct fn_field {int dummy; } ;
struct TYPE_2__ {struct value* (* virtual_fn_field ) (struct value**,struct fn_field*,int,struct type*,int) ;} ;

/* Variables and functions */
 TYPE_1__ current_cp_abi ; 
 struct value* stub1 (struct value**,struct fn_field*,int,struct type*,int) ; 

struct value *
value_virtual_fn_field (struct value **arg1p, struct fn_field *f, int j,
			struct type *type, int offset)
{
  if ((current_cp_abi.virtual_fn_field) == NULL)
    return NULL;
  return (*current_cp_abi.virtual_fn_field) (arg1p, f, j, type, offset);
}