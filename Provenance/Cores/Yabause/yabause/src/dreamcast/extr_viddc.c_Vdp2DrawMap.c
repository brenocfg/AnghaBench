#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; int patternpixelwh; int patternwh; int draww; float coordincx; int drawh; float coordincy; int mapwh; int y; int addr; int /*<<< orphan*/  (* PlaneAddr ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ vdp2draw_struct ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  Vdp2DrawPlane (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 scalar_t__ vdp2height ; 
 scalar_t__ vdp2width ; 

__attribute__((used)) static void Vdp2DrawMap(vdp2draw_struct *info)
{
    int i, j;
    int X, Y;
    u32 lastplane;

    X = info->x;
    lastplane=0xFFFFFFFF;

    info->patternpixelwh = 8 * info->patternwh;
    info->draww = (int)((float)vdp2width / info->coordincx);
    info->drawh = (int)((float)vdp2height / info->coordincy);

    for(i = 0;i < info->mapwh;i++)
    {
        Y = info->y;
        info->x = X;
        for(j = 0;j < info->mapwh;j++)
        {
            info->y = Y;
            info->PlaneAddr(info, info->mapwh * i + j);
            if (info->addr != lastplane)
            {
                Vdp2DrawPlane(info);
                lastplane = info->addr;
            }
        }
    }
}