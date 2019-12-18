#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fd_disp; scalar_t__ fd_fb; int /*<<< orphan*/  framebuffer_size; int /*<<< orphan*/  framebuffer_addr; } ;
typedef  TYPE_1__ sunxi_disp_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_layer_release (TYPE_1__*) ; 

__attribute__((used)) static int sunxi_disp_close(sunxi_disp_t *ctx)
{
   if (ctx->fd_disp >= 0)
   {
      /* release layer */
      sunxi_layer_release(ctx);
      /* close descriptors */
      munmap(ctx->framebuffer_addr, ctx->framebuffer_size);
      close(ctx->fd_fb);
      close(ctx->fd_disp);
      ctx->fd_disp = -1;
      free(ctx);
   }
   return 0;
}