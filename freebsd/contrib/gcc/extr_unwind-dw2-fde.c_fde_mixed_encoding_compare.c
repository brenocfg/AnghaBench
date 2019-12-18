#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pc_begin; } ;
typedef  TYPE_1__ fde ;
typedef  scalar_t__ _Unwind_Ptr ;

/* Variables and functions */
 int /*<<< orphan*/  base_from_object (int,struct object*) ; 
 int get_fde_encoding (TYPE_1__ const*) ; 
 int /*<<< orphan*/  read_encoded_value_with_base (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
fde_mixed_encoding_compare (struct object *ob, const fde *x, const fde *y)
{
  int x_encoding, y_encoding;
  _Unwind_Ptr x_ptr, y_ptr;

  x_encoding = get_fde_encoding (x);
  read_encoded_value_with_base (x_encoding, base_from_object (x_encoding, ob),
				x->pc_begin, &x_ptr);

  y_encoding = get_fde_encoding (y);
  read_encoded_value_with_base (y_encoding, base_from_object (y_encoding, ob),
				y->pc_begin, &y_ptr);

  if (x_ptr > y_ptr)
    return 1;
  if (x_ptr < y_ptr)
    return -1;
  return 0;
}