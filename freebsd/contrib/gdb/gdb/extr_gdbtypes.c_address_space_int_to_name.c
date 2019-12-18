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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int TYPE_FLAG_ADDRESS_CLASS_ALL ; 
 int TYPE_FLAG_CODE_SPACE ; 
 int TYPE_FLAG_DATA_SPACE ; 
 struct gdbarch* current_gdbarch ; 
 char const* gdbarch_address_class_type_flags_to_name (struct gdbarch*,int) ; 
 scalar_t__ gdbarch_address_class_type_flags_to_name_p (struct gdbarch*) ; 

const char *
address_space_int_to_name (int space_flag)
{
  struct gdbarch *gdbarch = current_gdbarch;
  if (space_flag & TYPE_FLAG_CODE_SPACE)
    return "code";
  else if (space_flag & TYPE_FLAG_DATA_SPACE)
    return "data";
  else if ((space_flag & TYPE_FLAG_ADDRESS_CLASS_ALL)
           && gdbarch_address_class_type_flags_to_name_p (gdbarch))
    return gdbarch_address_class_type_flags_to_name (gdbarch, space_flag);
  else
    return NULL;
}