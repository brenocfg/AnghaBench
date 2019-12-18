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
struct TYPE_2__ {int w; int line; int /*<<< orphan*/  szchar; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ry_rx (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_desa_addx_subx()
{
  if((d.w&0460)!=0400/* || (d.w&300==0300)*/)
    return 0;
  desa_ry_rx((d.line==0xD) ? 'ADDX' : 'SUBX', d.szchar);
  return 1;
}