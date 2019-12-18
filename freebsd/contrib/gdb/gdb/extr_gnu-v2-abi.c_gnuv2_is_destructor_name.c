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
typedef  enum dtor_kinds { ____Placeholder_dtor_kinds } dtor_kinds ;

/* Variables and functions */
 int complete_object_dtor ; 
 scalar_t__ is_cplus_marker (char const) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static enum dtor_kinds
gnuv2_is_destructor_name (const char *name)
{
  if ((name[0] == '_' && is_cplus_marker (name[1]) && name[2] == '_')
      || strncmp (name, "__dt__", 6) == 0)
    return complete_object_dtor;
  else
    return 0;
}