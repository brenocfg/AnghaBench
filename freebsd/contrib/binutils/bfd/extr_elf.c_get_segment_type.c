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
#define  PT_DYNAMIC 138 
#define  PT_GNU_EH_FRAME 137 
#define  PT_GNU_RELRO 136 
#define  PT_GNU_STACK 135 
#define  PT_INTERP 134 
#define  PT_LOAD 133 
#define  PT_NOTE 132 
#define  PT_NULL 131 
#define  PT_PHDR 130 
#define  PT_SHLIB 129 
#define  PT_TLS 128 

__attribute__((used)) static const char *
get_segment_type (unsigned int p_type)
{
  const char *pt;
  switch (p_type)
    {
    case PT_NULL: pt = "NULL"; break;
    case PT_LOAD: pt = "LOAD"; break;
    case PT_DYNAMIC: pt = "DYNAMIC"; break;
    case PT_INTERP: pt = "INTERP"; break;
    case PT_NOTE: pt = "NOTE"; break;
    case PT_SHLIB: pt = "SHLIB"; break;
    case PT_PHDR: pt = "PHDR"; break;
    case PT_TLS: pt = "TLS"; break;
    case PT_GNU_EH_FRAME: pt = "EH_FRAME"; break;
    case PT_GNU_STACK: pt = "STACK"; break;
    case PT_GNU_RELRO: pt = "RELRO"; break;
    default: pt = NULL; break;
    }
  return pt;
}