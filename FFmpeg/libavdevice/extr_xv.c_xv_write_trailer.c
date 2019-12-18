#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ display; scalar_t__ gc; TYPE_4__* yuv_image; int /*<<< orphan*/  yuv_shminfo; } ;
typedef  TYPE_1__ XVContext ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (scalar_t__) ; 
 int /*<<< orphan*/  XFree (TYPE_4__*) ; 
 int /*<<< orphan*/  XFreeGC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XShmDetach (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xv_write_trailer(AVFormatContext *s)
{
    XVContext *xv = s->priv_data;
    if (xv->display) {
        XShmDetach(xv->display, &xv->yuv_shminfo);
        if (xv->yuv_image)
            shmdt(xv->yuv_image->data);
        XFree(xv->yuv_image);
        if (xv->gc)
            XFreeGC(xv->display, xv->gc);
        XCloseDisplay(xv->display);
    }
    return 0;
}