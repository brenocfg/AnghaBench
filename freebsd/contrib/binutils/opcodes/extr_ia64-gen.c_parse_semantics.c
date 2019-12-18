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
 int IA64_DVS_DATA ; 
 int IA64_DVS_IMPLIED ; 
 int IA64_DVS_IMPLIEDF ; 
 int IA64_DVS_INSTR ; 
 int IA64_DVS_NONE ; 
 int IA64_DVS_OTHER ; 
 int IA64_DVS_SPECIFIC ; 
 int IA64_DVS_STOP ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
parse_semantics (char *sem)
{
  if (strcmp (sem, "none") == 0)
    return IA64_DVS_NONE;
  else if (strcmp (sem, "implied") == 0)
    return IA64_DVS_IMPLIED;
  else if (strcmp (sem, "impliedF") == 0)
    return IA64_DVS_IMPLIEDF;
  else if (strcmp (sem, "data") == 0)
    return IA64_DVS_DATA;
  else if (strcmp (sem, "instr") == 0)
    return IA64_DVS_INSTR;
  else if (strcmp (sem, "specific") == 0)
    return IA64_DVS_SPECIFIC;
  else if (strcmp (sem, "stop") == 0)
    return IA64_DVS_STOP;
  else 
    return IA64_DVS_OTHER;
}