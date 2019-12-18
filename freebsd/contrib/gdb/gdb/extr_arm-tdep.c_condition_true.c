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
 unsigned long FLAG_C ; 
 unsigned long FLAG_N ; 
 unsigned long FLAG_V ; 
 unsigned long FLAG_Z ; 
 unsigned long INST_AL ; 
#define  INST_CC 141 
#define  INST_CS 140 
#define  INST_EQ 139 
#define  INST_GE 138 
#define  INST_GT 137 
#define  INST_HI 136 
#define  INST_LE 135 
#define  INST_LS 134 
#define  INST_LT 133 
#define  INST_MI 132 
#define  INST_NE 131 
 unsigned long INST_NV ; 
#define  INST_PL 130 
#define  INST_VC 129 
#define  INST_VS 128 

__attribute__((used)) static int
condition_true (unsigned long cond, unsigned long status_reg)
{
  if (cond == INST_AL || cond == INST_NV)
    return 1;

  switch (cond)
    {
    case INST_EQ:
      return ((status_reg & FLAG_Z) != 0);
    case INST_NE:
      return ((status_reg & FLAG_Z) == 0);
    case INST_CS:
      return ((status_reg & FLAG_C) != 0);
    case INST_CC:
      return ((status_reg & FLAG_C) == 0);
    case INST_MI:
      return ((status_reg & FLAG_N) != 0);
    case INST_PL:
      return ((status_reg & FLAG_N) == 0);
    case INST_VS:
      return ((status_reg & FLAG_V) != 0);
    case INST_VC:
      return ((status_reg & FLAG_V) == 0);
    case INST_HI:
      return ((status_reg & (FLAG_C | FLAG_Z)) == FLAG_C);
    case INST_LS:
      return ((status_reg & (FLAG_C | FLAG_Z)) != FLAG_C);
    case INST_GE:
      return (((status_reg & FLAG_N) == 0) == ((status_reg & FLAG_V) == 0));
    case INST_LT:
      return (((status_reg & FLAG_N) == 0) != ((status_reg & FLAG_V) == 0));
    case INST_GT:
      return (((status_reg & FLAG_Z) == 0) &&
	      (((status_reg & FLAG_N) == 0) == ((status_reg & FLAG_V) == 0)));
    case INST_LE:
      return (((status_reg & FLAG_Z) != 0) ||
	      (((status_reg & FLAG_N) == 0) != ((status_reg & FLAG_V) == 0)));
    }
  return 1;
}