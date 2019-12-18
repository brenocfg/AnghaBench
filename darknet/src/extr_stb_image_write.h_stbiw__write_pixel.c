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
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;
typedef  TYPE_1__ stbi__write_context ;

/* Variables and functions */
 int /*<<< orphan*/  stbiw__write3 (TYPE_1__*,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void stbiw__write_pixel(stbi__write_context *s, int rgb_dir, int comp, int write_alpha, int expand_mono, unsigned char *d)
{
   unsigned char bg[3] = { 255, 0, 255}, px[3];
   int k;

   if (write_alpha < 0)
      s->func(s->context, &d[comp - 1], 1);

   switch (comp) {
      case 2: // 2 pixels = mono + alpha, alpha is written separately, so same as 1-channel case
      case 1:
         if (expand_mono)
            stbiw__write3(s, d[0], d[0], d[0]); // monochrome bmp
         else
            s->func(s->context, d, 1);  // monochrome TGA
         break;
      case 4:
         if (!write_alpha) {
            // composite against pink background
            for (k = 0; k < 3; ++k)
               px[k] = bg[k] + ((d[k] - bg[k]) * d[3]) / 255;
            stbiw__write3(s, px[1 - rgb_dir], px[1], px[1 + rgb_dir]);
            break;
         }
         /* FALLTHROUGH */
      case 3:
         stbiw__write3(s, d[1 - rgb_dir], d[1], d[1 + rgb_dir]);
         break;
   }
   if (write_alpha > 0)
      s->func(s->context, &d[comp - 1], 1);
}