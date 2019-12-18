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
#define  DT_PPC64_GLINK 130 
#define  DT_PPC64_OPD 129 
#define  DT_PPC64_OPDSZ 128 

__attribute__((used)) static const char *
get_ppc64_dynamic_type (unsigned long type)
{
  switch (type)
    {
    case DT_PPC64_GLINK: return "PPC64_GLINK";
    case DT_PPC64_OPD:   return "PPC64_OPD";
    case DT_PPC64_OPDSZ: return "PPC64_OPDSZ";
    default:
      return NULL;
    }
}