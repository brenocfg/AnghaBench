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
typedef  size_t bfd_reloc_code_real_type ;

/* Variables and functions */
 size_t BFD_RELOC_UNUSED ; 
 char const** bfd_reloc_code_real_names ; 

const char *
bfd_get_reloc_code_name (bfd_reloc_code_real_type code)
{
  if (code > BFD_RELOC_UNUSED)
    return 0;
  return bfd_reloc_code_real_names[code];
}