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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  disp; } ;
struct TYPE_8__ {int /*<<< orphan*/  pixmap; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  magic; int /*<<< orphan*/  surface; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  TYPE_2__* GRAPHICS_RESOURCE_HANDLE ;
typedef  int EGLBoolean ;

/* Variables and functions */
 scalar_t__ GX_PBUFFER ; 
 int /*<<< orphan*/  GX_TRACE (char*,...) ; 
 scalar_t__ GX_WINDOW ; 
 int /*<<< orphan*/  RES_MAGIC ; 
 TYPE_7__ display ; 
 int eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglWaitClient () ; 
 int /*<<< orphan*/  gx_priv_destroy_native_window (TYPE_2__*) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vgDestroyImage (int /*<<< orphan*/ ) ; 
 scalar_t__ vgGetError () ; 

int32_t graphics_delete_resource( GRAPHICS_RESOURCE_HANDLE res )
{
   EGLBoolean result;

   if (!res)
   {
      // let it slide - mimics old behaviour
      return 0;
   }
   GX_TRACE("delete resource @%p", res);

   vcos_assert(res->magic == RES_MAGIC);

   if (res->type == GX_PBUFFER)
   {
      GX_CLIENT_STATE_T save;
      gx_priv_save(&save, res);
      vgDestroyImage(res->u.pixmap);
      vcos_assert(vgGetError() == 0);
      gx_priv_restore(&save);
   }

   GX_TRACE("graphics_delete_resource: calling eglDestroySurface...");
   result = eglDestroySurface(display.disp, res->surface);
   vcos_assert(result);

   GX_TRACE("graphics_delete_resource: calling eglWaitClient...");
   eglWaitClient(); // wait for EGL to finish sorting out its surfaces

   if (res->type == GX_WINDOW)
   {
      GX_TRACE("graphics_delete_resource: calling gx_priv_destroy_native_window...");
      gx_priv_destroy_native_window(res);
   }

   res->magic = ~RES_MAGIC;
   vcos_free(res);
   GX_TRACE("graphics_delete_resource: done");

   return 0;
}