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
struct objfile {int dummy; } ;

/* Variables and functions */
#define  FT_BOOLEAN 140 
#define  FT_BYTE 139 
#define  FT_CHAR 138 
#define  FT_DBL_PREC_FLOAT 137 
#define  FT_FLOAT 136 
#define  FT_INTEGER 135 
#define  FT_LONG 134 
#define  FT_SHORT 133 
#define  FT_SIGNED_CHAR 132 
#define  FT_SIGNED_INTEGER 131 
#define  FT_SIGNED_LONG 130 
#define  FT_SIGNED_SHORT 129 
#define  FT_VOID 128 
 struct type* c_create_fundamental_type (struct objfile*,int) ; 
 struct type* java_boolean_type ; 
 struct type* java_byte_type ; 
 struct type* java_char_type ; 
 struct type* java_double_type ; 
 struct type* java_float_type ; 
 struct type* java_int_type ; 
 struct type* java_long_type ; 
 struct type* java_short_type ; 
 struct type* java_void_type ; 

__attribute__((used)) static struct type *
java_create_fundamental_type (struct objfile *objfile, int typeid)
{
  switch (typeid)
    {
    case FT_VOID:
      return java_void_type;
    case FT_BOOLEAN:
      return java_boolean_type;
    case FT_CHAR:
      return java_char_type;
    case FT_FLOAT:
      return java_float_type;
    case FT_DBL_PREC_FLOAT:
      return java_double_type;
    case FT_BYTE:
    case FT_SIGNED_CHAR:
      return java_byte_type;
    case FT_SHORT:
    case FT_SIGNED_SHORT:
      return java_short_type;
    case FT_INTEGER:
    case FT_SIGNED_INTEGER:
      return java_int_type;
    case FT_LONG:
    case FT_SIGNED_LONG:
      return java_long_type;
    }
  return c_create_fundamental_type (objfile, typeid);
}