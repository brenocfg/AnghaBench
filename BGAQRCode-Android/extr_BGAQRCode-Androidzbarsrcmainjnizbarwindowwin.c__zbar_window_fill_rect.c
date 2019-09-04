#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ point_t ;
struct TYPE_12__ {scalar_t__ member_3; scalar_t__ member_2; scalar_t__ member_1; scalar_t__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdc; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DC_BRUSH ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _zbar_window_fill_rect (zbar_window_t *w,
                            uint32_t rgb,
                            point_t org,
                            point_t size)
{
    HDC hdc = w->state->hdc;
    SetDCBrushColor(hdc, RGB((rgb & 4) * 0x33,
                             (rgb & 2) * 0x66,
                             (rgb & 1) * 0xcc));

    RECT r = { org.x, org.y, org.x + size.x, org.y + size.y };

    FillRect(hdc, &r, GetStockObject(DC_BRUSH));
    return(0);
}