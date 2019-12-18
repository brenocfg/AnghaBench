#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ dram; } ;

/* Variables and functions */
 TYPE_1__* svp ; 

__attribute__((used)) static u32 PicoRead16_svpca2(u32 a)
{
  u32 a1 = a >> 1;
  a1 = (a1 & 0x7801) | ((a1 & 0x1e) << 6) | ((a1 & 0x7e0) >> 4);
  return ((u16 *)svp->dram)[a1];
}