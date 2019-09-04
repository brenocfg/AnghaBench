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
#define  FE_DOWNWARD 131 
#define  FE_TONEAREST 130 
#define  FE_TOWARDZERO 129 
#define  FE_UPWARD 128 

const char *mode(int mode)
{
  switch(mode)
  {
    case FE_DOWNWARD: return "FE_DOWNWARD";
    case FE_TONEAREST: return "FE_TONEAREST";
    case FE_TOWARDZERO: return "FE_TOWARDZERO";
    case FE_UPWARD: return "FE_UPWARD";
    default: return "Unknown";
  }
}