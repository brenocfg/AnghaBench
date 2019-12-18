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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 int /*<<< orphan*/ * TYPE_NAME (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int common_val_print (struct value*,struct ui_file*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 

int
pascal_value_print (struct value *val, struct ui_file *stream, int format,
		    enum val_prettyprint pretty)
{
  struct type *type = VALUE_TYPE (val);

  /* If it is a pointer, indicate what it points to.

     Print type also if it is a reference.

     Object pascal: if it is a member pointer, we will take care
     of that when we print it.  */
  if (TYPE_CODE (type) == TYPE_CODE_PTR ||
      TYPE_CODE (type) == TYPE_CODE_REF)
    {
      /* Hack:  remove (char *) for char strings.  Their
         type is indicated by the quoted string anyway. */
      if (TYPE_CODE (type) == TYPE_CODE_PTR &&
	  TYPE_NAME (type) == NULL &&
	  TYPE_NAME (TYPE_TARGET_TYPE (type)) != NULL
	  && strcmp (TYPE_NAME (TYPE_TARGET_TYPE (type)), "char") == 0)
	{
	  /* Print nothing */
	}
      else
	{
	  fprintf_filtered (stream, "(");
	  type_print (type, "", stream, -1);
	  fprintf_filtered (stream, ") ");
	}
    }
  return common_val_print (val, stream, format, 1, 0, pretty);
}