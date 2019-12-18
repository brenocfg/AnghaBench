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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 unsigned int CHAR_TYPE_SIZE ; 
 unsigned int INT_TYPE_SIZE ; 
 unsigned int LONG_LONG_TYPE_SIZE ; 
 unsigned int LONG_TYPE_SIZE ; 
 unsigned int SHORT_TYPE_SIZE ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  long_integer_type_node ; 
 int /*<<< orphan*/  long_long_integer_type_node ; 
 int /*<<< orphan*/  long_long_unsigned_type_node ; 
 int /*<<< orphan*/  long_unsigned_type_node ; 
 int /*<<< orphan*/  make_signed_type (unsigned int) ; 
 int /*<<< orphan*/  make_unsigned_type (unsigned int) ; 
 int /*<<< orphan*/  short_integer_type_node ; 
 int /*<<< orphan*/  short_unsigned_type_node ; 
 int /*<<< orphan*/  signed_char_type_node ; 
 int /*<<< orphan*/  unsigned_char_type_node ; 
 int /*<<< orphan*/  unsigned_type_node ; 

__attribute__((used)) static tree
make_or_reuse_type (unsigned size, int unsignedp)
{
  if (size == INT_TYPE_SIZE)
    return unsignedp ? unsigned_type_node : integer_type_node;
  if (size == CHAR_TYPE_SIZE)
    return unsignedp ? unsigned_char_type_node : signed_char_type_node;
  if (size == SHORT_TYPE_SIZE)
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;
  if (size == LONG_TYPE_SIZE)
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;
  if (size == LONG_LONG_TYPE_SIZE)
    return (unsignedp ? long_long_unsigned_type_node
            : long_long_integer_type_node);

  if (unsignedp)
    return make_unsigned_type (size);
  else
    return make_signed_type (size);
}