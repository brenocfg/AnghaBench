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
#define  PT_HP_CORE_COMM 146 
#define  PT_HP_CORE_KERNEL 145 
#define  PT_HP_CORE_LOADABLE 144 
#define  PT_HP_CORE_MMF 143 
#define  PT_HP_CORE_NONE 142 
#define  PT_HP_CORE_PROC 141 
#define  PT_HP_CORE_SHM 140 
#define  PT_HP_CORE_STACK 139 
#define  PT_HP_CORE_UTSNAME 138 
#define  PT_HP_CORE_VERSION 137 
#define  PT_HP_FASTBIND 136 
#define  PT_HP_HSL_ANNOT 135 
#define  PT_HP_OPT_ANNOT 134 
#define  PT_HP_PARALLEL 133 
#define  PT_HP_STACK 132 
#define  PT_HP_TLS 131 
#define  PT_PARISC_ARCHEXT 130 
#define  PT_PARISC_UNWIND 129 
#define  PT_PARISC_WEAKORDER 128 

__attribute__((used)) static const char *
get_parisc_segment_type (unsigned long type)
{
  switch (type)
    {
    case PT_HP_TLS:		return "HP_TLS";
    case PT_HP_CORE_NONE:	return "HP_CORE_NONE";
    case PT_HP_CORE_VERSION:	return "HP_CORE_VERSION";
    case PT_HP_CORE_KERNEL:	return "HP_CORE_KERNEL";
    case PT_HP_CORE_COMM:	return "HP_CORE_COMM";
    case PT_HP_CORE_PROC:	return "HP_CORE_PROC";
    case PT_HP_CORE_LOADABLE:	return "HP_CORE_LOADABLE";
    case PT_HP_CORE_STACK:	return "HP_CORE_STACK";
    case PT_HP_CORE_SHM:	return "HP_CORE_SHM";
    case PT_HP_CORE_MMF:	return "HP_CORE_MMF";
    case PT_HP_PARALLEL:	return "HP_PARALLEL";
    case PT_HP_FASTBIND:	return "HP_FASTBIND";
    case PT_HP_OPT_ANNOT:	return "HP_OPT_ANNOT";
    case PT_HP_HSL_ANNOT:	return "HP_HSL_ANNOT";
    case PT_HP_STACK:		return "HP_STACK";
    case PT_HP_CORE_UTSNAME:	return "HP_CORE_UTSNAME";
    case PT_PARISC_ARCHEXT:	return "PARISC_ARCHEXT";
    case PT_PARISC_UNWIND:	return "PARISC_UNWIND";
    case PT_PARISC_WEAKORDER:	return "PARISC_WEAKORDER";
    default:
      break;
    }

  return NULL;
}