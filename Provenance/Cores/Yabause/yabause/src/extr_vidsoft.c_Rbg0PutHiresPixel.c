#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  linescreen; int /*<<< orphan*/  priority; int /*<<< orphan*/  (* PostPixelFetchCalc ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ vdp2draw_struct ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  COLSAT2YAB32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetAlpha (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TitanPutPixel (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void Rbg0PutHiresPixel(vdp2draw_struct *info, u32 color, u32 dot, int i, int j)
{
   u32 pixel = info->PostPixelFetchCalc(info, COLSAT2YAB32(GetAlpha(info, color, dot), color));
   int x_pos = i * 2;
   TitanPutPixel(info->priority, x_pos, j, pixel, info->linescreen, info);
   TitanPutPixel(info->priority, x_pos + 1, j, pixel, info->linescreen, info);
}