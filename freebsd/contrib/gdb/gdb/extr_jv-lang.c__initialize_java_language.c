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

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CODE_BOOL ; 
 int /*<<< orphan*/  TYPE_CODE_CHAR ; 
 int /*<<< orphan*/  TYPE_CODE_FLT ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  TYPE_CODE_VOID ; 
 int /*<<< orphan*/  TYPE_FLAG_UNSIGNED ; 
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 void* init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* java_boolean_type ; 
 void* java_byte_type ; 
 void* java_char_type ; 
 void* java_double_type ; 
 void* java_float_type ; 
 void* java_int_type ; 
 int /*<<< orphan*/  java_language_defn ; 
 void* java_long_type ; 
 void* java_short_type ; 
 void* java_void_type ; 

void
_initialize_java_language (void)
{

  java_int_type = init_type (TYPE_CODE_INT, 4, 0, "int", NULL);
  java_short_type = init_type (TYPE_CODE_INT, 2, 0, "short", NULL);
  java_long_type = init_type (TYPE_CODE_INT, 8, 0, "long", NULL);
  java_byte_type = init_type (TYPE_CODE_INT, 1, 0, "byte", NULL);
  java_boolean_type = init_type (TYPE_CODE_BOOL, 1, 0, "boolean", NULL);
  java_char_type = init_type (TYPE_CODE_CHAR, 2, TYPE_FLAG_UNSIGNED, "char", NULL);
  java_float_type = init_type (TYPE_CODE_FLT, 4, 0, "float", NULL);
  java_double_type = init_type (TYPE_CODE_FLT, 8, 0, "double", NULL);
  java_void_type = init_type (TYPE_CODE_VOID, 1, 0, "void", NULL);

  add_language (&java_language_defn);
}