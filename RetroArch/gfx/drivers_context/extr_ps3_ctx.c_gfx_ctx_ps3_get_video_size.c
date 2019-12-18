#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  gl_device; } ;
typedef  TYPE_1__ gfx_ctx_ps3_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  psglGetDeviceDimensions (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void gfx_ctx_ps3_get_video_size(void *data,
      unsigned *width, unsigned *height)
{
   gfx_ctx_ps3_data_t *ps3 = (gfx_ctx_ps3_data_t*)data;

#if defined(HAVE_PSGL)
   if (ps3)
      psglGetDeviceDimensions(ps3->gl_device, width, height);
#endif
}