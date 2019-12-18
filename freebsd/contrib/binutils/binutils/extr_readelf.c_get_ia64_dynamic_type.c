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
#define  DT_IA_64_PLT_RESERVE 128 

__attribute__((used)) static const char *
get_ia64_dynamic_type (unsigned long type)
{
  switch (type)
    {
    case DT_IA_64_PLT_RESERVE: return "IA_64_PLT_RESERVE";
    default:
      return NULL;
    }
}