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
 unsigned int FIX_VR4120_DIV ; 
 unsigned int FIX_VR4120_DMACC ; 
 unsigned int FIX_VR4120_DMULT ; 
 unsigned int FIX_VR4120_MACC ; 
 unsigned int FIX_VR4120_MTHILO ; 
 unsigned int FIX_VR4120_MULT ; 
 unsigned int NUM_FIX_VR4120_CLASSES ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static unsigned int
classify_vr4120_insn (const char *name)
{
  if (strncmp (name, "macc", 4) == 0)
    return FIX_VR4120_MACC;
  if (strncmp (name, "dmacc", 5) == 0)
    return FIX_VR4120_DMACC;
  if (strncmp (name, "mult", 4) == 0)
    return FIX_VR4120_MULT;
  if (strncmp (name, "dmult", 5) == 0)
    return FIX_VR4120_DMULT;
  if (strstr (name, "div"))
    return FIX_VR4120_DIV;
  if (strcmp (name, "mtlo") == 0 || strcmp (name, "mthi") == 0)
    return FIX_VR4120_MTHILO;
  return NUM_FIX_VR4120_CLASSES;
}