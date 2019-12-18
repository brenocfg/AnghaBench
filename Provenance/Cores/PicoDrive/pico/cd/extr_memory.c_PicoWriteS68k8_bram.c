#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* bram; } ;
struct TYPE_3__ {int changed; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 TYPE_1__ SRam ; 

__attribute__((used)) static void PicoWriteS68k8_bram(u32 a, u32 d)
{
  Pico_mcd->bram[(a >> 1) & 0x1fff] = d;
  SRam.changed = 1;
}