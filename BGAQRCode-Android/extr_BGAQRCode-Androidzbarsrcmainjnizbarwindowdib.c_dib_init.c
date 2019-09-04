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
struct TYPE_10__ {int dst_width; int /*<<< orphan*/  dst_height; TYPE_4__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_11__ {int width; int /*<<< orphan*/  height; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_9__ {int biWidth; int /*<<< orphan*/  biHeight; } ;
struct TYPE_12__ {TYPE_1__ bih; } ;
typedef  TYPE_4__ window_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_window_bih_init (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int dib_init (zbar_window_t *w,
                     zbar_image_t *img,
                     int new_format)
{
    if(new_format)
        _zbar_window_bih_init(w, img);

    window_state_t *win = w->state;
    w->dst_width = win->bih.biWidth = (img->width + 3) & ~3;
    w->dst_height = win->bih.biHeight = img->height;
    return(0);
}