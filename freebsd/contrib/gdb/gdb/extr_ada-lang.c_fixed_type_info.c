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
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_INT ; 
 int TYPE_CODE_RANGE ; 
 int TYPE_CODE_UNDEF ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 char* ada_type_name (struct type*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static const char *
fixed_type_info (struct type *type)
{
  const char *name = ada_type_name (type);
  enum type_code code = (type == NULL) ? TYPE_CODE_UNDEF : TYPE_CODE (type);

  if ((code == TYPE_CODE_INT || code == TYPE_CODE_RANGE) && name != NULL)
    {
      const char *tail = strstr (name, "___XF_");
      if (tail == NULL)
	return NULL;
      else
	return tail + 5;
    }
  else if (code == TYPE_CODE_RANGE && TYPE_TARGET_TYPE (type) != type)
    return fixed_type_info (TYPE_TARGET_TYPE (type));
  else
    return NULL;
}