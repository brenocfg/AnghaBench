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
typedef  int /*<<< orphan*/  png_image_read_control ;

/* Variables and functions */
 int /*<<< orphan*/  P_sRGB ; 
 int /*<<< orphan*/  png_create_colormap_entry (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_gray_colormap(png_image_read_control *display)
{
   unsigned int i;

   for (i=0; i<256; ++i)
      png_create_colormap_entry(display, i, i, i, i, 255, P_sRGB);

   return (int)i;
}