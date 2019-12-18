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
struct TYPE_7__ {int /*<<< orphan*/  shmid; int /*<<< orphan*/  shmaddr; } ;
struct TYPE_6__ {scalar_t__ font; TYPE_1__* font_driver; struct TYPE_6__* vtable; struct TYPE_6__* utable; struct TYPE_6__* ytable; int /*<<< orphan*/  image; TYPE_4__ shminfo; } ;
typedef  TYPE_2__ xv_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XShmDetach (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  x11_colormap_destroy () ; 
 int /*<<< orphan*/  x11_input_ctx_destroy () ; 
 int /*<<< orphan*/  x11_window_destroy (int) ; 

__attribute__((used)) static void xv_free(void *data)
{
   xv_t *xv = (xv_t*)data;

   if (!xv)
      return;

   x11_input_ctx_destroy();

   XShmDetach(g_x11_dpy, &xv->shminfo);
   shmdt(xv->shminfo.shmaddr);
   shmctl(xv->shminfo.shmid, IPC_RMID, NULL);
   XFree(xv->image);

   x11_window_destroy(true);
   x11_colormap_destroy();

   XCloseDisplay(g_x11_dpy);

   free(xv->ytable);
   free(xv->utable);
   free(xv->vtable);

   if (xv->font)
      xv->font_driver->free(xv->font);

   free(xv);
}