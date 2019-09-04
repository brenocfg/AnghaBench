#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; int /*<<< orphan*/  bih; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hdd; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_6__ {scalar_t__ data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ zbar_image_t ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DDF_SAME_DRAW ; 
 int /*<<< orphan*/  DrawDibDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ValidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfw_draw (zbar_window_t *w,
                     zbar_image_t *img)
{
    HDC hdc = GetDC(w->hwnd);
    if(!hdc)
        return(-1/*FIXME*/);

    zprintf(24, "DrawDibDraw(%dx%d -> %dx%d)\n",
            img->width, img->height, w->width, w->height);

    DrawDibDraw(w->hdd, hdc,
                0, 0, w->width, w->height,
                &w->bih, (void*)img->data,
                0, 0, w->src_width, w->src_height,
                DDF_SAME_DRAW);

    ValidateRect(w->hwnd, NULL);
    ReleaseDC(w->hwnd, hdc);
    return(0);
}