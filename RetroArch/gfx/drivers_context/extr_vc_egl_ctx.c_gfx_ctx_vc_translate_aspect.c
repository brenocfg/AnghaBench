#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static float gfx_ctx_vc_translate_aspect(void *data,
      unsigned width, unsigned height)
{
   (void)data;
   /* Check for SD televisions: they should always be 4:3. */
   if ((width == 640 || width == 720) && (height == 480 || height == 576))
      return 4.0f / 3.0f;
   return (float)width / height;
}