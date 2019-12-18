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
 scalar_t__ HighCol ; 
 int /*<<< orphan*/  PDRAW_SHHI_DONE ; 
 int /*<<< orphan*/  rendstatus ; 

__attribute__((used)) static void DrawTilesFromCacheShPrep(void)
{
  // as some layer has covered whole line with hi priority tiles,
  // we can process whole line and then act as if sh/hi mode was off,
  // but leave lo pri op sprite markers alone
  int c = 320/4, *zb = (int *)(HighCol+8);
  rendstatus |= PDRAW_SHHI_DONE;
  while (c--)
  {
    *zb++ &= 0xbfbfbfbf;
  }
}