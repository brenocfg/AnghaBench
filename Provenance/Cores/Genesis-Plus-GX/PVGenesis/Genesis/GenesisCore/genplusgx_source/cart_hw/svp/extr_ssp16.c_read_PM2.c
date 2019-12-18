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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int /*<<< orphan*/  elprintf (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_io (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rPM2 ; 

__attribute__((used)) static u32 read_PM2(void)
{
  u32 d = pm_io(2, 0, 0);
  if (d != (u32)-1) return d;
  /* can be removed? */
#ifdef LOG_SVP
  elprintf(EL_SVP|EL_ANOMALY, "PM2 raw r %04x @ %04x", rPM2, GET_PPC_OFFS());
#endif
  return rPM2;
}