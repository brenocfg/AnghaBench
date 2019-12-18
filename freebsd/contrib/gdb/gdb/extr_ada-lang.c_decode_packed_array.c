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
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* coerce_unspec_val_to_type (struct value*,int /*<<< orphan*/ ,struct type*) ; 
 struct type* decode_packed_array_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static struct value *
decode_packed_array (struct value *arr)
{
  struct type *type = decode_packed_array_type (VALUE_TYPE (arr));

  if (type == NULL)
    {
      error ("can't unpack array");
      return NULL;
    }
  else
    return coerce_unspec_val_to_type (arr, 0, type);
}