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
typedef  int /*<<< orphan*/  vdp1cmd_struct ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_3__ {double linenumber; double texturestep; double xredstep; double xgreenstep; double xbluestep; int previousStep; scalar_t__ endcodesdetected; } ;
typedef  TYPE_1__ DrawLineData ;

/* Variables and functions */
 int /*<<< orphan*/  DrawLineCallback ; 
 int iterateOverLine (int,int,int,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DrawLine(int x1, int y1, int x2, int y2, int greedy, double linenumber, double texturestep, double xredstep, double xgreenstep, double xbluestep, Vdp1* regs, vdp1cmd_struct *cmd, u8 * ram, u8* back_framebuffer)
{
	DrawLineData data;

	data.linenumber = linenumber;
	data.texturestep = texturestep;
	data.xredstep = xredstep;
	data.xgreenstep = xgreenstep;
	data.xbluestep = xbluestep;
	data.endcodesdetected = 0;
	data.previousStep = 123456789;

   return iterateOverLine(x1, y1, x2, y2, greedy, &data, DrawLineCallback, regs, cmd, ram, back_framebuffer);
}