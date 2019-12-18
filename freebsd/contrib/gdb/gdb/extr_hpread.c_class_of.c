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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 scalar_t__ TYPE_CODE_PTR ; 
 char* TYPE_FIELD_NAME (struct type*,int /*<<< orphan*/ ) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 char* TYPE_NAME (struct type*) ; 
 scalar_t__ TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
class_of (struct type *functype)
{
  struct type *first_param_type;
  char *first_param_name;
  struct type *pointed_to_type;
  char *class_name;

  /* Check that the function has a first argument "this",
   * and that "this" is a pointer to a class. If not,
   * functype is not a member function, so return NULL.
   */
  if (TYPE_NFIELDS (functype) == 0)
    return NULL;
  first_param_name = TYPE_FIELD_NAME (functype, 0);
  if (first_param_name == NULL)
    return NULL;		/* paranoia */
  if (strcmp (first_param_name, "this"))
    return NULL;
  first_param_type = TYPE_FIELD_TYPE (functype, 0);
  if (first_param_type == NULL)
    return NULL;		/* paranoia */
  if (TYPE_CODE (first_param_type) != TYPE_CODE_PTR)
    return NULL;

  /* Get the thing that "this" points to, check that
   * it's a class, and get its class name.
   */
  pointed_to_type = TYPE_TARGET_TYPE (first_param_type);
  if (pointed_to_type == NULL)
    return NULL;		/* paranoia */
  if (TYPE_CODE (pointed_to_type) != TYPE_CODE_CLASS)
    return NULL;
  class_name = TYPE_NAME (pointed_to_type);
  if (class_name == NULL)
    return NULL;		/* paranoia */

  /* The class name may be of the form "class c", in which case
   * we want to strip off the leading "class ".
   */
  if (strncmp (class_name, "class ", 6) == 0)
    class_name += 6;

  return class_name;
}