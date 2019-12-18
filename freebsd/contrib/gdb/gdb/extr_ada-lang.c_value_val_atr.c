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
 scalar_t__ TYPE_CODE_ENUM ; 
 long TYPE_FIELD_BITPOS (struct type*,long) ; 
 long TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  discrete_type_p (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  integer_type_p (int /*<<< orphan*/ ) ; 
 long value_as_long (struct value*) ; 
 struct value* value_from_longest (struct type*,long) ; 

__attribute__((used)) static struct value *
value_val_atr (struct type *type, struct value *arg)
{
  if (!discrete_type_p (type))
    error ("'VAL only defined on discrete types");
  if (!integer_type_p (VALUE_TYPE (arg)))
    error ("'VAL requires integral argument");

  if (TYPE_CODE (type) == TYPE_CODE_ENUM)
    {
      long pos = value_as_long (arg);
      if (pos < 0 || pos >= TYPE_NFIELDS (type))
	error ("argument to 'VAL out of range");
      return value_from_longest (type, TYPE_FIELD_BITPOS (type, pos));
    }
  else
    return value_from_longest (type, value_as_long (arg));
}