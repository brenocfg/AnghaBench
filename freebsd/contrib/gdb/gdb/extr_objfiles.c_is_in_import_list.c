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
struct objfile {int import_list_size; scalar_t__* import_list; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (char*,scalar_t__) ; 

int
is_in_import_list (char *name, struct objfile *objfile)
{
  int i;

  if (!objfile || !name || !*name)
    return 0;

  for (i = 0; i < objfile->import_list_size; i++)
    if (objfile->import_list[i] && DEPRECATED_STREQ (name, objfile->import_list[i]))
      return 1;
  return 0;
}