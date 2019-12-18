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
 scalar_t__ TYPE_CODE_ENUM ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 char* strstr (char const*,char*) ; 
 char* type_name_no_tag (struct type*) ; 

const char *
ada_renaming_type (struct type *type)
{
  if (type != NULL && TYPE_CODE (type) == TYPE_CODE_ENUM)
    {
      const char *name = type_name_no_tag (type);
      const char *suffix = (name == NULL) ? NULL : strstr (name, "___XR");
      if (suffix == NULL
	  || (suffix[5] != '\000' && strchr ("PES_", suffix[5]) == NULL))
	return NULL;
      else
	return suffix + 3;
    }
  else
    return NULL;
}