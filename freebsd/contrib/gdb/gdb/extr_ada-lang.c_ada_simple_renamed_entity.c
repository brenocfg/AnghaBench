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
struct symbol {int dummy; } ;

/* Variables and functions */
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 char* TYPE_FIELD_NAME (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* xmalloc (int) ; 

const char *
ada_simple_renamed_entity (struct symbol *sym)
{
  struct type *type;
  const char *raw_name;
  int len;
  char *result;

  type = SYMBOL_TYPE (sym);
  if (type == NULL || TYPE_NFIELDS (type) < 1)
    error ("Improperly encoded renaming.");

  raw_name = TYPE_FIELD_NAME (type, 0);
  len = (raw_name == NULL ? 0 : strlen (raw_name)) - 5;
  if (len <= 0)
    error ("Improperly encoded renaming.");

  result = xmalloc (len + 1);
  /* FIXME: add_name_string_cleanup should be defined in parse.c */
  /*  add_name_string_cleanup (result); */
  strncpy (result, raw_name, len);
  result[len] = '\000';
  return result;
}