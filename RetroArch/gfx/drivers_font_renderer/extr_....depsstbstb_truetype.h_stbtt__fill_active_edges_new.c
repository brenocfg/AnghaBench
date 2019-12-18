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
struct TYPE_4__ {float ey; float fdx; float fx; float fdy; float sy; int direction; struct TYPE_4__* next; } ;
typedef  TYPE_1__ stbtt__active_edge ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 float fabs (float) ; 
 int /*<<< orphan*/  stbtt__handle_clipped_edge (float*,int,TYPE_1__*,float,float,float,float) ; 

__attribute__((used)) static void stbtt__fill_active_edges_new(float *scanline, float *scanline_fill,
      int len, stbtt__active_edge *e, float y_top)
{
   float y_bottom = y_top+1;

   while (e)
   {
      /* brute force every pixel */

      /* compute intersection points with top & bottom */
      assert(e->ey >= y_top);

      if (e->fdx == 0) {
         float x0 = e->fx;
         if (x0 < len) {
            if (x0 >= 0) {
               stbtt__handle_clipped_edge(scanline,(int) x0,e, x0,y_top, x0,y_bottom);
               stbtt__handle_clipped_edge(scanline_fill-1,(int) x0+1,e, x0,y_top, x0,y_bottom);
            } else {
               stbtt__handle_clipped_edge(scanline_fill-1,0,e, x0,y_top, x0,y_bottom);
            }
         }
      } else {
         float x0 = e->fx;
         float dx = e->fdx;
         float xb = x0 + dx;
         float x_top, x_bottom;
         float y0,y1;
         float dy = e->fdy;
         assert(e->sy <= y_bottom && e->ey >= y_top);

         /* compute endpoints of line segment clipped to this scanline (if the
          * line segment starts on this scanline. x0 is the intersection of the
          * line with y_top, but that may be off the line segment.
          */
         if (e->sy > y_top) {
            x_top = x0 + dx * (e->sy - y_top);
            y0 = e->sy;
         } else {
            x_top = x0;
            y0 = y_top;
         }
         if (e->ey < y_bottom) {
            x_bottom = x0 + dx * (e->ey - y_top);
            y1 = e->ey;
         } else {
            x_bottom = xb;
            y1 = y_bottom;
         }

         if (x_top >= 0 && x_bottom >= 0 && x_top < len && x_bottom < len)
         {
            /* from here on, we don't have to range check x values */

            if ((int) x_top == (int) x_bottom)
            {
               /* simple case, only spans one pixel */

               float height;
               int x = (int) x_top;
               height = y1 - y0;
               assert(x >= 0 && x < len);
               scanline[x] += e->direction * (1-((x_top - x) + (x_bottom-x))/2)  * height;
               scanline_fill[x] += e->direction * height; /* everything right of this pixel is filled */
            }
            else
            {
               int x,x1,x2;
               float y_crossing, step, sign, area;

               /* covers 2+ pixels */
               if (x_top > x_bottom)
               {
                  /* flip scanline vertically; signed area is the same */
                  float t;
                  y0 = y_bottom - (y0 - y_top);
                  y1 = y_bottom - (y1 - y_top);
                   t = y0;
                   y0 = y1;
                   y1 = t;
                   t = x_bottom;
                   x_bottom = x_top;
                   x_top = t;
                  dx = -dx;
                  dy = -dy;
                   t = x0;
                   x0 = xb;
                   xb = t;
               }

               x1 = (int) x_top;
               x2 = (int) x_bottom;
               /* compute intersection with y axis at x1+1 */
               y_crossing = (x1+1 - x0) * dy + y_top;

               sign = e->direction;
               /* area of the rectangle covered from y0..y_crossing */
               area = sign * (y_crossing-y0);
               /* area of the triangle (x_top,y0), (x+1,y0), (x+1,y_crossing) */
               scanline[x1] += area * (1-((x_top - x1)+(x1+1-x1))/2);

               step = sign * dy;
               for (x = x1+1; x < x2; ++x)
               {
                  scanline[x] += area + step/2;
                  area += step;
               }
               y_crossing += dy * (x2 - (x1+1));

               assert(fabs(area) <= 1.01f);

               scanline[x2] += area + sign * (1-((x2-x2)+(x_bottom-x2))/2) * (y1-y_crossing);

               scanline_fill[x2] += sign * (y1-y0);
            }
         }
         else
         {
            /* if edge goes outside of box we're drawing, we require
             * clipping logic. since this does not match the intended use
             * of this library, we use a different, very slow brute
             * force implementation
             */
            int x;

            for (x=0; x < len; ++x)
            {
               /* cases:
                *
                * there can be up to two intersections with the pixel. any intersection
                * with left or right edges can be handled by splitting into two (or three)
                * regions. intersections with top & bottom do not necessitate case-wise logic.
                */
               float y0,y1;
               float y_cur = y_top, x_cur = x0;

               y0 = (x - x0) / dx + y_top;
               y1 = (x+1 - x0) / dx + y_top;

               if (y0 < y1) {
                  if (y0 > y_top && y0 < y_bottom) {
                     stbtt__handle_clipped_edge(scanline,x,e, x_cur,y_cur, (float) x,y0);
                     y_cur = y0;
                     x_cur = (float) x;
                  }
                  if (y1 >= y_cur && y1 < y_bottom) {
                     stbtt__handle_clipped_edge(scanline,x,e, x_cur,y_cur, (float) x+1,y1);
                     y_cur = y1;
                     x_cur = (float) x+1;
                  }
               } else {
                  if (y1 >= y_cur && y1 < y_bottom) {
                     stbtt__handle_clipped_edge(scanline,x,e, x_cur,y_cur, (float) x+1,y1);
                     y_cur = y1;
                     x_cur = (float) x+1;
                  }
                  if (y0 > y_top && y0 < y_bottom) {
                     stbtt__handle_clipped_edge(scanline,x,e, x_cur,y_cur, (float) x,y0);
                     y_cur = y0;
                     x_cur = (float) x;
                  }
               }
               stbtt__handle_clipped_edge(scanline,x,e, x_cur,y_cur, xb,y_bottom);
            }
         }
      }
      e = e->next;
   }
}