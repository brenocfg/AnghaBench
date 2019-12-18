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
typedef  int bfd_format ;

/* Variables and functions */
#define  bfd_archive 130 
#define  bfd_core 129 
#define  bfd_object 128 
 scalar_t__ bfd_type_end ; 
 scalar_t__ bfd_unknown ; 

const char *
bfd_format_string (bfd_format format)
{
  if (((int) format < (int) bfd_unknown)
      || ((int) format >= (int) bfd_type_end))
    return "invalid";

  switch (format)
    {
    case bfd_object:
      return "object";		/* Linker/assembler/compiler output.  */
    case bfd_archive:
      return "archive";		/* Object archive file.  */
    case bfd_core:
      return "core";		/* Core dump.  */
    default:
      return "unknown";
    }
}