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

/* Variables and functions */
#define  SHT_PARISC_ANNOT 134 
#define  SHT_PARISC_DLKM 133 
#define  SHT_PARISC_DOC 132 
#define  SHT_PARISC_EXT 131 
#define  SHT_PARISC_STUBS 130 
#define  SHT_PARISC_SYMEXTN 129 
#define  SHT_PARISC_UNWIND 128 

__attribute__((used)) static const char *
get_parisc_section_type_name (unsigned int sh_type)
{
  switch (sh_type)
    {
    case SHT_PARISC_EXT:	return "PARISC_EXT";
    case SHT_PARISC_UNWIND:	return "PARISC_UNWIND";
    case SHT_PARISC_DOC:	return "PARISC_DOC";
    case SHT_PARISC_ANNOT:	return "PARISC_ANNOT";
    case SHT_PARISC_SYMEXTN:	return "PARISC_SYMEXTN";
    case SHT_PARISC_STUBS:	return "PARISC_STUBS";
    case SHT_PARISC_DLKM:	return "PARISC_DLKM";
    default:
      break;
    }
  return NULL;
}