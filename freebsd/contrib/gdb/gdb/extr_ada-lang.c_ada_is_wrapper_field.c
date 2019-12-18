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
 scalar_t__ DEPRECATED_STREQ (char const*,char*) ; 
 scalar_t__ DEPRECATED_STREQN (char const*,char*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 

int
ada_is_wrapper_field (struct type *type, int field_num)
{
  const char *name = TYPE_FIELD_NAME (type, field_num);
  return (name != NULL
	  && (DEPRECATED_STREQN (name, "PARENT", 6) || DEPRECATED_STREQ (name, "REP")
	      || DEPRECATED_STREQN (name, "_parent", 7)
	      || name[0] == 'S' || name[0] == 'R' || name[0] == 'O'));
}