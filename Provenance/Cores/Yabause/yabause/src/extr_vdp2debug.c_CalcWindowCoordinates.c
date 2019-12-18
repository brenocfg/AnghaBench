#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int xstart; int ystart; int xend; int yend; } ;
typedef  TYPE_1__ clipping_struct ;

/* Variables and functions */
 int /*<<< orphan*/  ReadWindowCoordinates (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2Regs ; 

__attribute__((used)) static void CalcWindowCoordinates(int num, int *hstart, int *vstart, int *hend, int *vend)
{
   clipping_struct clip;
   ReadWindowCoordinates(num, &clip, Vdp2Regs);
   *hstart = clip.xstart;
   *vstart = clip.ystart;
   *hend = clip.xend;
   *vend = clip.yend;
}