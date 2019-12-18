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
typedef  int u32 ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_UIO ; 
 int PicoVideoRead (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 PicoRead16_vdp(u32 a)
{
  if ((a & 0x00e0) == 0x0000)
    return PicoVideoRead(a);

  elprintf(EL_UIO|EL_ANOMALY, "68k bad read [%06x] @%06x", a, SekPc);
  return 0;
}