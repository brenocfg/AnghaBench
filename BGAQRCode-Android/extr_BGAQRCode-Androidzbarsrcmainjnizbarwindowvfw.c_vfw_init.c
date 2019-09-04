#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int biWidth; int /*<<< orphan*/  biHeight; } ;
struct TYPE_8__ {int dst_width; int /*<<< orphan*/  hwnd; TYPE_7__ bih; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hdd; int /*<<< orphan*/  dst_height; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ zbar_image_t ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DrawDibBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zbar_window_bih_init (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int vfw_init (zbar_window_t *w,
                     zbar_image_t *img,
                     int new_format)
{
    if(new_format)
        _zbar_window_bih_init(w, img);

    w->dst_width = w->bih.biWidth = (img->width + 3) & ~3;
    w->dst_height = w->bih.biHeight = img->height;

    HDC hdc = GetDC(w->hwnd);
    if(!hdc)
        return(-1/*FIXME*/);

    if(!DrawDibBegin(w->hdd, hdc, w->width, w->height,
                     &w->bih, img->width, img->height, 0))
        return(-1/*FIXME*/);

    ReleaseDC(w->hwnd, hdc);
    return(0);
}