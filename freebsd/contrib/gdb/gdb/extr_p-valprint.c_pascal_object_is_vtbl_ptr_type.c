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
 int /*<<< orphan*/  pascal_vtbl_ptr_name ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* type_name_no_tag (struct type*) ; 

int
pascal_object_is_vtbl_ptr_type (struct type *type)
{
  char *typename = type_name_no_tag (type);

  return (typename != NULL
	  && strcmp (typename, pascal_vtbl_ptr_name) == 0);
}