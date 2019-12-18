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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char) ; 
 struct type* java_boolean_type ; 
 struct type* java_byte_type ; 
 struct type* java_char_type ; 
 struct type* java_double_type ; 
 struct type* java_float_type ; 
 struct type* java_int_type ; 
 struct type* java_long_type ; 
 struct type* java_short_type ; 
 struct type* java_void_type ; 

struct type *
java_primitive_type (int signature)
{
  switch (signature)
    {
    case 'B':
      return java_byte_type;
    case 'S':
      return java_short_type;
    case 'I':
      return java_int_type;
    case 'J':
      return java_long_type;
    case 'Z':
      return java_boolean_type;
    case 'C':
      return java_char_type;
    case 'F':
      return java_float_type;
    case 'D':
      return java_double_type;
    case 'V':
      return java_void_type;
    }
  error ("unknown signature '%c' for primitive type", (char) signature);
}