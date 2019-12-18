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
struct TYPE_3__ {int resize; int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ mali_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VT_ACTIVATE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void gfx_ctx_mali_fbdev_destroy(void *data)
{
   int fd;
   mali_ctx_data_t *mali = (mali_ctx_data_t*)data;

   if (mali)
   {
#ifdef HAVE_EGL
       egl_destroy(&mali->egl);
#endif

       mali->resize       = false;
       free(mali);
   }

   /* Clear framebuffer and set cursor on again */
   fd = open("/dev/tty", O_RDWR);
   ioctl(fd, VT_ACTIVATE, 5);
   ioctl(fd, VT_ACTIVATE, 1);
   close(fd);

   system("setterm -cursor on");
}