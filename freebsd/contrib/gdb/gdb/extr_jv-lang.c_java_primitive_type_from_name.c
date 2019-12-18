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
 struct type* java_boolean_type ; 
 struct type* java_byte_type ; 
 struct type* java_char_type ; 
 struct type* java_double_type ; 
 struct type* java_float_type ; 
 struct type* java_int_type ; 
 struct type* java_long_type ; 
 struct type* java_short_type ; 
 struct type* java_void_type ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

struct type *
java_primitive_type_from_name (char *name, int namelen)
{
  switch (name[0])
    {
    case 'b':
      if (namelen == 4 && memcmp (name, "byte", 4) == 0)
	return java_byte_type;
      if (namelen == 7 && memcmp (name, "boolean", 7) == 0)
	return java_boolean_type;
      break;
    case 'c':
      if (namelen == 4 && memcmp (name, "char", 4) == 0)
	return java_char_type;
    case 'd':
      if (namelen == 6 && memcmp (name, "double", 6) == 0)
	return java_double_type;
      break;
    case 'f':
      if (namelen == 5 && memcmp (name, "float", 5) == 0)
	return java_float_type;
      break;
    case 'i':
      if (namelen == 3 && memcmp (name, "int", 3) == 0)
	return java_int_type;
      break;
    case 'l':
      if (namelen == 4 && memcmp (name, "long", 4) == 0)
	return java_long_type;
      break;
    case 's':
      if (namelen == 5 && memcmp (name, "short", 5) == 0)
	return java_short_type;
      break;
    case 'v':
      if (namelen == 4 && memcmp (name, "void", 4) == 0)
	return java_void_type;
      break;
    }
  return NULL;
}