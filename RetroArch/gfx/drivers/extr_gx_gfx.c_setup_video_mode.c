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
struct TYPE_5__ {int /*<<< orphan*/ * framebuf; } ;
typedef  TYPE_1__ gx_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_K0_TO_K1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORIENTATION_NORMAL ; 
 int /*<<< orphan*/  OSInitThreadQueue (int /*<<< orphan*/ *) ; 
 int VI_DISPLAY_PIX_SZ ; 
 int /*<<< orphan*/  g_orientation ; 
 int /*<<< orphan*/  g_video_cond ; 
 int /*<<< orphan*/  gx_get_video_output_size (TYPE_1__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  gx_set_video_mode (TYPE_1__*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  memalign (int,int) ; 

__attribute__((used)) static void setup_video_mode(gx_video_t *gx)
{
   unsigned width, height;

   if (!gx->framebuf[0])
   {
      unsigned i;
      for (i = 0; i < 2; i++)
         gx->framebuf[i] = MEM_K0_TO_K1(
               memalign(32, 640 * 576 * VI_DISPLAY_PIX_SZ));
   }

   g_orientation      = ORIENTATION_NORMAL;
   OSInitThreadQueue(&g_video_cond);

   gx_get_video_output_size(gx, &width, &height);
   gx_set_video_mode(gx, width, height, true);
}