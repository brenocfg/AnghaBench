#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbiw_uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ stbi__write_context ;

/* Variables and functions */
 scalar_t__ stbi__flip_vertically_on_write ; 
 int /*<<< orphan*/  stbiw__write_pixel (TYPE_1__*,int,int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stbiw__write_pixels(stbi__write_context *s, int rgb_dir, int vdir, int x, int y, int comp, void *data, int write_alpha, int scanline_pad, int expand_mono)
{
   stbiw_uint32 zero = 0;
   int i,j, j_end;

   if (y <= 0)
      return;

   if (stbi__flip_vertically_on_write)
      vdir *= -1;

   if (vdir < 0)
      j_end = -1, j = y-1;
   else
      j_end =  y, j = 0;

   for (; j != j_end; j += vdir) {
      for (i=0; i < x; ++i) {
         unsigned char *d = (unsigned char *) data + (j*x+i)*comp;
         stbiw__write_pixel(s, rgb_dir, comp, write_alpha, expand_mono, d);
      }
      s->func(s->context, &zero, scanline_pad);
   }
}