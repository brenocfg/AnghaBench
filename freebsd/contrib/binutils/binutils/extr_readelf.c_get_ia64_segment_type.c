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
#define  PT_HP_TLS 133 
#define  PT_IA_64_ARCHEXT 132 
#define  PT_IA_64_HP_HSL_ANOT 131 
#define  PT_IA_64_HP_OPT_ANOT 130 
#define  PT_IA_64_HP_STACK 129 
#define  PT_IA_64_UNWIND 128 

__attribute__((used)) static const char *
get_ia64_segment_type (unsigned long type)
{
  switch (type)
    {
    case PT_IA_64_ARCHEXT:	return "IA_64_ARCHEXT";
    case PT_IA_64_UNWIND:	return "IA_64_UNWIND";
    case PT_HP_TLS:		return "HP_TLS";
    case PT_IA_64_HP_OPT_ANOT:	return "HP_OPT_ANNOT";
    case PT_IA_64_HP_HSL_ANOT:	return "HP_HSL_ANNOT";
    case PT_IA_64_HP_STACK:	return "HP_STACK";
    default:
      break;
    }

  return NULL;
}