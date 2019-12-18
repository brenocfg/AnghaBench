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
 int TYPE_FLAG_CODE_SPACE ; 
 int TYPE_FLAG_DATA_SPACE ; 
 struct gdbarch* current_gdbarch ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ gdbarch_address_class_name_to_type_flags (struct gdbarch*,char*,int*) ; 
 scalar_t__ gdbarch_address_class_name_to_type_flags_p (struct gdbarch*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

extern int
address_space_name_to_int (char *space_identifier)
{
  struct gdbarch *gdbarch = current_gdbarch;
  int type_flags;
  /* Check for known address space delimiters. */
  if (!strcmp (space_identifier, "code"))
    return TYPE_FLAG_CODE_SPACE;
  else if (!strcmp (space_identifier, "data"))
    return TYPE_FLAG_DATA_SPACE;
  else if (gdbarch_address_class_name_to_type_flags_p (gdbarch)
           && gdbarch_address_class_name_to_type_flags (gdbarch,
							space_identifier,
							&type_flags))
    return type_flags;
  else
    error ("Unknown address space specifier: \"%s\"", space_identifier);
}