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
 unsigned char* DrawLineDest ; 
 scalar_t__ HighCol ; 
 int POPT_DIS_32C_BORDER ; 
 int PicoOpt ; 
 int /*<<< orphan*/  memcpy32 (int*,int*,int) ; 

__attribute__((used)) static void FinalizeLine8bitM4(int line)
{
  unsigned char *pd = DrawLineDest;

  if (!(PicoOpt & POPT_DIS_32C_BORDER))
    pd += 32;

  memcpy32((int *)pd, (int *)(HighCol+8), 256/4);
}