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
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* type_name_no_tag (struct type*) ; 
 int /*<<< orphan*/  vtbl_ptr_name ; 

int
cp_is_vtbl_ptr_type (struct type *type)
{
  char *typename = type_name_no_tag (type);

  return (typename != NULL && !strcmp (typename, vtbl_ptr_name));
}