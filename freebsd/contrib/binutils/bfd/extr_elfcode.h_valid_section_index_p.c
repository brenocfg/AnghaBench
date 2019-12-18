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
typedef  int bfd_boolean ;

/* Variables and functions */
 unsigned int SHN_HIOS ; 
 unsigned int SHN_HIRESERVE ; 
 unsigned int SHN_LOPROC ; 
 unsigned int SHN_LORESERVE ; 

__attribute__((used)) static inline bfd_boolean
valid_section_index_p (unsigned index, unsigned num_sections)
{
  /* Note: We allow SHN_UNDEF as a valid section index.  */
  if (index < SHN_LORESERVE || index > SHN_HIRESERVE)
    return index < num_sections;
  
  /* We disallow the use of reserved indcies, except for those
     with OS or Application specific meaning.  The test make use
     of the knowledge that:
       SHN_LORESERVE == SHN_LOPROC
     and
       SHN_HIPROC == SHN_LOOS - 1  */
  /* XXX - Should we allow SHN_XINDEX as a valid index here ?  */
  return (index >= SHN_LOPROC && index <= SHN_HIOS);
}